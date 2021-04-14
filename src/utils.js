// @ts-ignore
const {
  DeviceClass,
  DeviceInformation,
} = require('@nodert-win10-rs4/windows.devices.enumeration');
const { StorageDevice } = require('@nodert-win10-rs4/windows.devices.portable');
const { format } = require('date-fns');
const {
  QueryOptions,
  CommonFileQuery,
  CommonFolderQuery,
} = require('@nodert-win10-rs4/windows.storage.search');
const {
  ThumbnailMode,
} = require('@nodert-win10-rs4/windows.storage.fileproperties');
const {
  FileInformationFactory,
} = require('@nodert-win10-rs4/windows.storage.bulkaccess');
const {
  IVectorView,
} = require('@nodert-win10-rs4/windows.foundation.collections');
const { promisify } = require('util');

const SUPPORTED_FILE_EXTENSIONS = [
  '.jpg',
  '.jpeg',
  '.png',
  '.tif',
  '.tiff',
  '.bmp',
  '.heic',
];
const WINDOWS_PORTABLE_DEVICE_GUID = '{6AC27878-A6FA-4155-BA85-F98F491D4F33}';

const getDevices = async (filter = {}) => {
  const deviceClass = DeviceClass.portableStorageDevice;
  const findAsync = promisify(DeviceInformation.findAllAsync);
  const connectedDevices = await findAsync(deviceClass);
  const deviceIterator = connectedDevices.first();
  const mobileDevies = [];
  while (deviceIterator && deviceIterator.hasCurrent) {
    const { id: deviceId, name: deviceName } = deviceIterator.current;
    if (deviceId.toUpperCase().includes(WINDOWS_PORTABLE_DEVICE_GUID)) {
      const mobile = {};
      mobile.deviceId = deviceId;
      mobile.description = deviceName;
      filter.deviceId !== deviceId && mobileDevies.push(mobile);
    }
    deviceIterator.moveNext();
  }
  return mobileDevies;
};

const isFile = path => {
  const regExp = /\..+?$/;
  return regExp.test(path);
};

const mapFolder = f => ({
  type: 'folder',
  dateCreated: f.dateCreated,
  displayName: f.displayName,
  displayType: f.displayType,
  folderRelativeId: f.folderRelativeId,
  name: f.name,
  path: f.path,
  children: f.children,
  ref: f,
});

const mapFile = f => ({
  type: 'file',
  contentType: f.contentType,
  dateCreated: format(new Date(f.dateCreated), 'yyyy-MM-dd HH:mm:ss'),
  displayName: f.displayName,
  displayType: f.displayType,
  fileType: f.fileType,
  folderRelativeId: f.folderRelativeId,
  isAvailable: f.isAvailable,
  name: f.name,
  path: f.path,
  // rotation: f.imageProperties?.orientation,
  // width: f.imageProperties?.width,
  // height: f.imageProperties?.height,
  // children: f.children,
  ref: f,
});

const mapItem = f => (isFile(f) ? mapFile(f) : mapFolder(f));

const getStorage = async deviceId => {
  const storage = StorageDevice.fromId(deviceId);
  return storage;
};

const getFolders = async storage => {
  const folder = storage?.ref || storage;
  const queryOptions = new QueryOptions(CommonFolderQuery.defaultQuery);
  const query = folder.createFolderQueryWithOptions(queryOptions);
  const getFoldersAsync = promisify(query.getFoldersAsync.bind(query));
  const results = await getFoldersAsync();
  const folders = [];
  try {
    const folderIterator = results.first();
    while (folderIterator.hasCurrent) {
      ref = folderIterator.current;
      const folder = mapFolder(ref);
      folders.push(folder);
      folderIterator.moveNext();
    }
  } catch (e) {
    console.error('getFolders', e.message);
  }
  return folders;
};

const getFiles = async storage => {
  const folder = storage?.ref || storage;
  const queryOptions = new QueryOptions(
    CommonFileQuery.defaultQuery,
    SUPPORTED_FILE_EXTENSIONS
  );
  const query = folder.createFileQueryWithOptions(queryOptions);
  // const fileInfo = new FileInformationFactory(
  //   query,
  //   ThumbnailMode.singleItem,
  //   256
  // );
  const getFilesAsync = promisify(query.getFilesAsync.bind(query));
  const files = await getFilesAsync();
  const items = [];
  try {
    const fileIterator = files.first();
    while (fileIterator.hasCurrent) {
      const item = fileIterator.current;
      items.push(mapFile(item));
      fileIterator.moveNext();
    }
  } catch (e) {
    console.error('getFiles', e.message);
  }
  return items;
};

const getRecursiveItems = async folder => {
  const files = await getFiles(folder);
  const subfolders = await getFolders(folder);
  // folder.children = [...files.map(mapFile), ...subfolders.map(mapFolder)];
  folder.children = [...files, ...subfolders];
  if (!subfolders.length) return folder.children;
  for (let subfolder of subfolders) {
    let items = [];
    try {
      items =
        subfolder.folderRelativeId.includes('Android') ||
        subfolder.folderRelativeId.includes('data') ||
        subfolder.folderRelativeId.includes('tencent')
          ? []
          : await getRecursiveItems(subfolder);
      // items = await getRecursiveItems(subfolder);
    } catch (e) {
      console.error('getRecursiveItems', e);
      subfolder.children = [];
      break;
    }
    // subfolder.children = [...items.map(mapItem)];
    subfolder.children = [...items];
  }
  return folder.children || [];
};

module.exports = {
  getDevices,
  getStorage,
  getFolders,
  getFiles,
  getRecursiveItems,
  mapItem,
};
