// @ts-ignore
const { DeviceClass, DeviceInformation } = require('@nodert-win10-rs4/windows.devices.enumeration');
const { StorageDevice } = require('@nodert-win10-rs4/windows.devices.portable');
const { QueryOptions, CommonFileQuery, CommonFolderQuery } = require('@nodert-win10-rs4/windows.storage.search');
const { StorageFolder, StorageFile, NameCollisionOption } = require('@nodert-win10-rs4/windows.storage');
const { IVectorView } = require('@nodert-win10-rs4/windows.foundation.collections');
const { promisify } = require('util');

const SUPPORTED_FILE_EXTENSIONS = ['.jpg', '.jpeg', '.png', '.tif', '.tiff', '.bmp', '.heic'];
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

const getStorage = async (deviceId) => {
  const storage = StorageDevice.fromId(deviceId);
  return storage;
};

const getFolders = async (storage) => {
  const queryOptions = new QueryOptions(
    CommonFolderQuery.defaultQuery,
  );
  const query = storage.createFolderQueryWithOptions(queryOptions);
  const getFoldersAsync = promisify(query.getFoldersAsync.bind(query));
  const results = await getFoldersAsync();
  const folders = [];
  try {
    const folderIterator = results.first();
    while (folderIterator.hasCurrent) {
      folders.push(folderIterator.current);
      folderIterator.moveNext();
    }
  } catch (e) {
    console.error(e);
  }
  return folders;
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
});

const mapFile = f => ({
  type: 'file', 
  contentType: f.contentType,
  dateCreated: f.dateCreated,
  displayName: f.displayName,
  displayType: f.displayType,
  fileType: f.fileType,
  folderRelativeId: f.folderRelativeId,
  isAvailable: f.isAvailable,
  name: f.name,
  path: f.path,
  children: f.children,
})

const mapItem = f => isFile(f) ? mapFile(f) : mapFolder(f);

const getRecursiveItems = async (folder) => {
  const files = await getFiles(folder)
  const subfolders = await getFolders(folder);
  folder.children = [...files, ...subfolders]
  if (!subfolders.length) {
    return folder.children;
  } else {
    for (let subfolder of subfolders) {
      const items = await getRecursiveItems(subfolder);     
      subfolder.children = [...items];
    }
    return folder.children;
  }
}

const getFiles = async (storage) => {
  const queryOptions = new QueryOptions(
    CommonFileQuery.defaultQuery,
    SUPPORTED_FILE_EXTENSIONS
  );
  const query = storage.createFileQueryWithOptions(queryOptions);
  const getFilesAsync = promisify(query.getFilesAsync.bind(query));
  const files = await getFilesAsync();
  const items = [];
  try {
    const fileIterator = files.first();
    while (fileIterator.hasCurrent) {
      items.push(fileIterator.current);
      fileIterator.moveNext();
    }
  } catch (e) {
    console.error(e);
  }
  return items;
};

const getItems = async (storage) => {
  const query = storage.createItemQuery();
  const getItemsAsync = promisify(query.getItemsAsync.bind(query));
  const result = await getItemsAsync(0, 10);
  const items = [];
  try {
    const itemIterator = result.first();
    while (itemIterator.hasCurrent) {
      items.push(itemIterator.current);
      itemIterator.moveNext();
    }
  } catch (e) {
    console.error(e);
  }
  return items;
};

module.exports = {
  getDevices,
  getStorage,
  getFolders,
  getFiles,
  getItems,
  getRecursiveItems,
  mapItem,
}