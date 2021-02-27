_KnownLibraryId = function() {
  this.music = 0;
  this.pictures = 1;
  this.videos = 2;
  this.documents = 3;
};
exports.KnownLibraryId = new _KnownLibraryId();

_KnownFolderId = function() {
  this.appCaptures = 0;
  this.cameraRoll = 1;
  this.documentsLibrary = 2;
  this.homeGroup = 3;
  this.mediaServerDevices = 4;
  this.musicLibrary = 5;
  this.objects3D = 6;
  this.picturesLibrary = 7;
  this.playlists = 8;
  this.recordedCalls = 9;
  this.removableDevices = 10;
  this.savedPictures = 11;
  this.screenshots = 12;
  this.videosLibrary = 13;
  this.allAppMods = 14;
  this.currentAppMods = 15;
};
exports.KnownFolderId = new _KnownFolderId();

_CreationCollisionOption = function() {
  this.generateUniqueName = 0;
  this.replaceExisting = 1;
  this.failIfExists = 2;
  this.openIfExists = 3;
};
exports.CreationCollisionOption = new _CreationCollisionOption();

_NameCollisionOption = function() {
  this.generateUniqueName = 0;
  this.replaceExisting = 1;
  this.failIfExists = 2;
};
exports.NameCollisionOption = new _NameCollisionOption();

_StorageDeleteOption = function() {
  this.default = 0;
  this.permanentDelete = 1;
};
exports.StorageDeleteOption = new _StorageDeleteOption();

_StorageItemTypes = function() {
  this.none = 0;
  this.file = 1;
  this.folder = 2;
};
exports.StorageItemTypes = new _StorageItemTypes();

_FileAttributes = function() {
  this.normal = 0;
  this.readOnly = 1;
  this.directory = 2;
  this.archive = 3;
  this.temporary = 4;
  this.locallyIncomplete = 5;
};
exports.FileAttributes = new _FileAttributes();

_FileAccessMode = function() {
  this.read = 0;
  this.readWrite = 1;
};
exports.FileAccessMode = new _FileAccessMode();

_StorageLibraryChangeType = function() {
  this.created = 0;
  this.deleted = 1;
  this.movedOrRenamed = 2;
  this.contentsChanged = 3;
  this.movedOutOfLibrary = 4;
  this.movedIntoLibrary = 5;
  this.contentsReplaced = 6;
  this.indexingStatusChanged = 7;
  this.encryptionChanged = 8;
  this.changeTrackingLost = 9;
};
exports.StorageLibraryChangeType = new _StorageLibraryChangeType();

_StreamedFileFailureMode = function() {
  this.failed = 0;
  this.currentlyUnavailable = 1;
  this.incomplete = 2;
};
exports.StreamedFileFailureMode = new _StreamedFileFailureMode();

_StorageOpenOptions = function() {
  this.none = 0;
  this.allowOnlyReaders = 1;
  this.allowReadersAndWriters = 2;
};
exports.StorageOpenOptions = new _StorageOpenOptions();

_ApplicationDataLocality = function() {
  this.local = 0;
  this.roaming = 1;
  this.temporary = 2;
  this.localCache = 3;
};
exports.ApplicationDataLocality = new _ApplicationDataLocality();

_ApplicationDataCreateDisposition = function() {
  this.always = 0;
  this.existing = 1;
};
exports.ApplicationDataCreateDisposition = new _ApplicationDataCreateDisposition();

StorageLibrary = (function() {
  var cls = function StorageLibrary() {
    this.folders = new Object();
    this.saveFolder = new StorageFolder();
    this.changeTracker = new StorageLibraryChangeTracker();
  };

  cls.prototype.requestAddFolderAsync = function requestAddFolderAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.requestRemoveFolderAsync = function requestRemoveFolderAsync(folder, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="folder" type="StorageFolder">A param.</param>
    /// </signature>
  };

  cls.prototype.areFolderSuggestionsAvailableAsync = function areFolderSuggestionsAvailableAsync(
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.getLibraryForUserAsync = function getLibraryForUserAsync(user, libraryId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <param name="libraryId" type="KnownLibraryId">A param.</param>
    /// </signature>
  };

  cls.getLibraryAsync = function getLibraryAsync(libraryId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="libraryId" type="KnownLibraryId">A param.</param>
    /// </signature>
  };

  cls.prototype.addListener = function addListener(eventName, callback) {};
  cls.prototype.removeListener = function removeListener(eventName, callback) {};
  cls.prototype.on = function on(eventName, callback) {};
  cls.prototype.off = function off(eventName, callback) {};
  return cls;
})();
exports.StorageLibrary = StorageLibrary;

StorageFolder = (function() {
  var cls = function StorageFolder() {
    this.attributes = new FileAttributes();
    this.dateCreated = new Date();
    this.name = new String();
    this.path = new String();
    this.displayName = new String();
    this.displayType = new String();
    this.folderRelativeId = new String();
    this.properties = new Object();
    this.provider = new StorageProvider();
  };

  cls.prototype.createFileAsync = function createFileAsync(desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.createFileAsync = function createFileAsync(desiredName, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="options" type="CreationCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.createFolderAsync = function createFolderAsync(desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.createFolderAsync = function createFolderAsync(desiredName, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="options" type="CreationCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.getFileAsync = function getFileAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.getFolderAsync = function getFolderAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.getItemAsync = function getItemAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.getFilesAsync = function getFilesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.getFilesAsync = function getFilesAsync(
    query,
    startIndex,
    maxItemsToRetrieve,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="query" type="Number">A param.</param>
    /// <param name="startIndex" type="Number">A param.</param>
    /// <param name="maxItemsToRetrieve" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getFilesAsync = function getFilesAsync(query, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="query" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getFoldersAsync = function getFoldersAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.getFoldersAsync = function getFoldersAsync(
    query,
    startIndex,
    maxItemsToRetrieve,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="query" type="Number">A param.</param>
    /// <param name="startIndex" type="Number">A param.</param>
    /// <param name="maxItemsToRetrieve" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getFoldersAsync = function getFoldersAsync(query, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="query" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getItemsAsync = function getItemsAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.getItemsAsync = function getItemsAsync(startIndex, maxItemsToRetrieve, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="startIndex" type="Number">A param.</param>
    /// <param name="maxItemsToRetrieve" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.renameAsync = function renameAsync(desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.renameAsync = function renameAsync(desiredName, option, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="option" type="NameCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.deleteAsync = function deleteAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.deleteAsync = function deleteAsync(option, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="option" type="StorageDeleteOption">A param.</param>
    /// </signature>
  };

  cls.prototype.getBasicPropertiesAsync = function getBasicPropertiesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.getIndexedStateAsync = function getIndexedStateAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(mode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(mode, requestedSize, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(
    mode,
    requestedSize,
    options,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// <param name="options" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getScaledImageAsThumbnailAsync = function getScaledImageAsThumbnailAsync(
    mode,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getScaledImageAsThumbnailAsync = function getScaledImageAsThumbnailAsync(
    mode,
    requestedSize,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getScaledImageAsThumbnailAsync = function getScaledImageAsThumbnailAsync(
    mode,
    requestedSize,
    options,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// <param name="options" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getParentAsync = function getParentAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.tryGetItemAsync = function tryGetItemAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.tryGetChangeTracker = function tryGetChangeTracker() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="StorageLibraryChangeTracker" />
    /// </signature>
    return new StorageLibraryChangeTracker();
  };

  cls.prototype.isOfType = function isOfType(type) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="type" type="StorageItemTypes">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.prototype.createFileQuery = function createFileQuery() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.createFileQuery = function createFileQuery(query) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="query" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.createFileQueryWithOptions = function createFileQueryWithOptions(queryOptions) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="queryOptions" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.createFolderQuery = function createFolderQuery() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.createFolderQuery = function createFolderQuery(query) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="query" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.createFolderQueryWithOptions = function createFolderQueryWithOptions(queryOptions) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="queryOptions" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.createItemQuery = function createItemQuery() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.createItemQueryWithOptions = function createItemQueryWithOptions(queryOptions) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="queryOptions" type="Object">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.areQueryOptionsSupported = function areQueryOptionsSupported(queryOptions) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="queryOptions" type="Object">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.prototype.isCommonFolderQuerySupported = function isCommonFolderQuerySupported(query) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="query" type="Number">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.prototype.isCommonFileQuerySupported = function isCommonFileQuerySupported(query) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="query" type="Number">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.prototype.isEqual = function isEqual(item) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="item" type="IStorageItem">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.getFolderFromPathAsync = function getFolderFromPathAsync(path, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="path" type="String">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.StorageFolder = StorageFolder;

StorageLibraryChangeTracker = (function() {
  var cls = function StorageLibraryChangeTracker() {};

  cls.prototype.getChangeReader = function getChangeReader() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="StorageLibraryChangeReader" />
    /// </signature>
    return new StorageLibraryChangeReader();
  };

  cls.prototype.enable = function enable() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.reset = function reset() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  return cls;
})();
exports.StorageLibraryChangeTracker = StorageLibraryChangeTracker;

KnownFolders = (function() {
  var cls = function KnownFolders() {};

  cls.getFolderForUserAsync = function getFolderForUserAsync(user, folderId, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <param name="folderId" type="KnownFolderId">A param.</param>
    /// </signature>
  };

  cls.cameraRoll = new StorageFolder();
  cls.playlists = new StorageFolder();
  cls.savedPictures = new StorageFolder();
  cls.documentsLibrary = new StorageFolder();
  cls.homeGroup = new StorageFolder();
  cls.mediaServerDevices = new StorageFolder();
  cls.musicLibrary = new StorageFolder();
  cls.picturesLibrary = new StorageFolder();
  cls.removableDevices = new StorageFolder();
  cls.videosLibrary = new StorageFolder();
  cls.appCaptures = new StorageFolder();
  cls.objects3D = new StorageFolder();
  cls.recordedCalls = new StorageFolder();
  return cls;
})();
exports.KnownFolders = KnownFolders;

UserDataPaths = (function() {
  var cls = function UserDataPaths() {
    this.cameraRoll = new String();
    this.cookies = new String();
    this.desktop = new String();
    this.documents = new String();
    this.downloads = new String();
    this.favorites = new String();
    this.history = new String();
    this.internetCache = new String();
    this.localAppData = new String();
    this.localAppDataLow = new String();
    this.music = new String();
    this.pictures = new String();
    this.profile = new String();
    this.recent = new String();
    this.roamingAppData = new String();
    this.savedPictures = new String();
    this.screenshots = new String();
    this.templates = new String();
    this.videos = new String();
  };

  cls.getForUser = function getForUser(user) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <returns type="UserDataPaths" />
    /// </signature>
    return new UserDataPaths();
  };

  cls.getDefault = function getDefault() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="UserDataPaths" />
    /// </signature>
    return new UserDataPaths();
  };

  return cls;
})();
exports.UserDataPaths = UserDataPaths;

AppDataPaths = (function() {
  var cls = function AppDataPaths() {
    this.cookies = new String();
    this.desktop = new String();
    this.documents = new String();
    this.favorites = new String();
    this.history = new String();
    this.internetCache = new String();
    this.localAppData = new String();
    this.programData = new String();
    this.roamingAppData = new String();
  };

  cls.getForUser = function getForUser(user) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <returns type="AppDataPaths" />
    /// </signature>
    return new AppDataPaths();
  };

  cls.getDefault = function getDefault() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="AppDataPaths" />
    /// </signature>
    return new AppDataPaths();
  };

  return cls;
})();
exports.AppDataPaths = AppDataPaths;

SystemDataPaths = (function() {
  var cls = function SystemDataPaths() {
    this.fonts = new String();
    this.programData = new String();
    this.public = new String();
    this.publicDesktop = new String();
    this.publicDocuments = new String();
    this.publicDownloads = new String();
    this.publicMusic = new String();
    this.publicPictures = new String();
    this.publicVideos = new String();
    this.system = new String();
    this.systemArm = new String();
    this.systemHost = new String();
    this.systemX64 = new String();
    this.systemX86 = new String();
    this.userProfiles = new String();
    this.windows = new String();
  };

  cls.getDefault = function getDefault() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="SystemDataPaths" />
    /// </signature>
    return new SystemDataPaths();
  };

  return cls;
})();
exports.SystemDataPaths = SystemDataPaths;

StorageFile = (function() {
  var cls = function StorageFile() {
    this.contentType = new String();
    this.fileType = new String();
    this.isAvailable = new Boolean();
    this.attributes = new FileAttributes();
    this.dateCreated = new Date();
    this.name = new String();
    this.path = new String();
    this.displayName = new String();
    this.displayType = new String();
    this.folderRelativeId = new String();
    this.properties = new Object();
    this.provider = new StorageProvider();
  };

  cls.prototype.openAsync = function openAsync(accessMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="accessMode" type="FileAccessMode">A param.</param>
    /// </signature>
  };

  cls.prototype.openAsync = function openAsync(accessMode, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="accessMode" type="FileAccessMode">A param.</param>
    /// <param name="options" type="StorageOpenOptions">A param.</param>
    /// </signature>
  };

  cls.prototype.openTransactedWriteAsync = function openTransactedWriteAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.openTransactedWriteAsync = function openTransactedWriteAsync(options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="options" type="StorageOpenOptions">A param.</param>
    /// </signature>
  };

  cls.prototype.copyAsync = function copyAsync(destinationFolder, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// </signature>
  };

  cls.prototype.copyAsync = function copyAsync(destinationFolder, desiredNewName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// <param name="desiredNewName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.copyAsync = function copyAsync(
    destinationFolder,
    desiredNewName,
    option,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// <param name="desiredNewName" type="String">A param.</param>
    /// <param name="option" type="NameCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.copyAndReplaceAsync = function copyAndReplaceAsync(fileToReplace, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="fileToReplace" type="IStorageFile">A param.</param>
    /// </signature>
  };

  cls.prototype.moveAsync = function moveAsync(destinationFolder, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// </signature>
  };

  cls.prototype.moveAsync = function moveAsync(destinationFolder, desiredNewName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// <param name="desiredNewName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.moveAsync = function moveAsync(
    destinationFolder,
    desiredNewName,
    option,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// <param name="desiredNewName" type="String">A param.</param>
    /// <param name="option" type="NameCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.moveAndReplaceAsync = function moveAndReplaceAsync(fileToReplace, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="fileToReplace" type="IStorageFile">A param.</param>
    /// </signature>
  };

  cls.prototype.renameAsync = function renameAsync(desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.renameAsync = function renameAsync(desiredName, option, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="option" type="NameCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.deleteAsync = function deleteAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.deleteAsync = function deleteAsync(option, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="option" type="StorageDeleteOption">A param.</param>
    /// </signature>
  };

  cls.prototype.getBasicPropertiesAsync = function getBasicPropertiesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.openReadAsync = function openReadAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.openSequentialReadAsync = function openSequentialReadAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(mode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(mode, requestedSize, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(
    mode,
    requestedSize,
    options,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// <param name="options" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getScaledImageAsThumbnailAsync = function getScaledImageAsThumbnailAsync(
    mode,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getScaledImageAsThumbnailAsync = function getScaledImageAsThumbnailAsync(
    mode,
    requestedSize,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getScaledImageAsThumbnailAsync = function getScaledImageAsThumbnailAsync(
    mode,
    requestedSize,
    options,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// <param name="options" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getParentAsync = function getParentAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.isOfType = function isOfType(type) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="type" type="StorageItemTypes">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.prototype.isEqual = function isEqual(item) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="item" type="IStorageItem">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.getFileFromPathAsync = function getFileFromPathAsync(path, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="path" type="String">A param.</param>
    /// </signature>
  };

  cls.getFileFromApplicationUriAsync = function getFileFromApplicationUriAsync(uri, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="uri" type="Object">A param.</param>
    /// </signature>
  };

  cls.createStreamedFileAsync = function createStreamedFileAsync(
    displayNameWithExtension,
    dataRequested,
    thumbnail,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="displayNameWithExtension" type="String">A param.</param>
    /// <param name="dataRequested" type="Object">A param.</param>
    /// <param name="thumbnail" type="Object">A param.</param>
    /// </signature>
  };

  cls.replaceWithStreamedFileAsync = function replaceWithStreamedFileAsync(
    fileToReplace,
    dataRequested,
    thumbnail,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="fileToReplace" type="IStorageFile">A param.</param>
    /// <param name="dataRequested" type="Object">A param.</param>
    /// <param name="thumbnail" type="Object">A param.</param>
    /// </signature>
  };

  cls.createStreamedFileFromUriAsync = function createStreamedFileFromUriAsync(
    displayNameWithExtension,
    uri,
    thumbnail,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="displayNameWithExtension" type="String">A param.</param>
    /// <param name="uri" type="Object">A param.</param>
    /// <param name="thumbnail" type="Object">A param.</param>
    /// </signature>
  };

  cls.replaceWithStreamedFileFromUriAsync = function replaceWithStreamedFileFromUriAsync(
    fileToReplace,
    uri,
    thumbnail,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="fileToReplace" type="IStorageFile">A param.</param>
    /// <param name="uri" type="Object">A param.</param>
    /// <param name="thumbnail" type="Object">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.StorageFile = StorageFile;

DownloadsFolder = (function() {
  var cls = function DownloadsFolder() {};

  cls.createFileForUserAsync = function createFileForUserAsync(user, desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.createFileForUserAsync = function createFileForUserAsync(
    user,
    desiredName,
    option,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="option" type="CreationCollisionOption">A param.</param>
    /// </signature>
  };

  cls.createFolderForUserAsync = function createFolderForUserAsync(user, desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.createFolderForUserAsync = function createFolderForUserAsync(
    user,
    desiredName,
    option,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="option" type="CreationCollisionOption">A param.</param>
    /// </signature>
  };

  cls.createFileAsync = function createFileAsync(desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.createFileAsync = function createFileAsync(desiredName, option, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="option" type="CreationCollisionOption">A param.</param>
    /// </signature>
  };

  cls.createFolderAsync = function createFolderAsync(desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.createFolderAsync = function createFolderAsync(desiredName, option, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="option" type="CreationCollisionOption">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.DownloadsFolder = DownloadsFolder;

IStorageItem = (function() {
  var cls = function IStorageItem() {
    this.attributes = new FileAttributes();
    this.dateCreated = new Date();
    this.name = new String();
    this.path = new String();
  };

  cls.prototype.renameAsync = function renameAsync(desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.renameAsync = function renameAsync(desiredName, option, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="option" type="NameCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.deleteAsync = function deleteAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.deleteAsync = function deleteAsync(option, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="option" type="StorageDeleteOption">A param.</param>
    /// </signature>
  };

  cls.prototype.getBasicPropertiesAsync = function getBasicPropertiesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.isOfType = function isOfType(type) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="type" type="StorageItemTypes">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  return cls;
})();
exports.IStorageItem = IStorageItem;

StorageLibraryChange = (function() {
  var cls = function StorageLibraryChange() {
    this.changeType = new StorageLibraryChangeType();
    this.path = new String();
    this.previousPath = new String();
  };

  cls.prototype.getStorageItemAsync = function getStorageItemAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.isOfType = function isOfType(type) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="type" type="StorageItemTypes">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  return cls;
})();
exports.StorageLibraryChange = StorageLibraryChange;

StorageLibraryChangeReader = (function() {
  var cls = function StorageLibraryChangeReader() {};

  cls.prototype.readBatchAsync = function readBatchAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.acceptChangesAsync = function acceptChangesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  return cls;
})();
exports.StorageLibraryChangeReader = StorageLibraryChangeReader;

IStreamedFileDataRequest = (function() {
  var cls = function IStreamedFileDataRequest() {};

  cls.prototype.failAndClose = function failAndClose(failureMode) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="failureMode" type="StreamedFileFailureMode">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.IStreamedFileDataRequest = IStreamedFileDataRequest;

StreamedFileDataRequest = (function() {
  var cls = function StreamedFileDataRequest() {};

  cls.prototype.writeAsync = function writeAsync(buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="buffer" type="Object">A param.</param>
    /// </signature>
  };

  cls.prototype.flushAsync = function flushAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.close = function close() {};

  cls.prototype.failAndClose = function failAndClose(failureMode) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="failureMode" type="StreamedFileFailureMode">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.StreamedFileDataRequest = StreamedFileDataRequest;

StorageStreamTransaction = (function() {
  var cls = function StorageStreamTransaction() {
    this.stream = new Object();
  };

  cls.prototype.commitAsync = function commitAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.close = function close() {};

  return cls;
})();
exports.StorageStreamTransaction = StorageStreamTransaction;

IStorageFolder = (function() {
  var cls = function IStorageFolder() {};

  cls.prototype.createFileAsync = function createFileAsync(desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.createFileAsync = function createFileAsync(desiredName, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="options" type="CreationCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.createFolderAsync = function createFolderAsync(desiredName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.createFolderAsync = function createFolderAsync(desiredName, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredName" type="String">A param.</param>
    /// <param name="options" type="CreationCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.getFileAsync = function getFileAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.getFolderAsync = function getFolderAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.getItemAsync = function getItemAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.getFilesAsync = function getFilesAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.getFoldersAsync = function getFoldersAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.getItemsAsync = function getItemsAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  return cls;
})();
exports.IStorageFolder = IStorageFolder;

IStorageFile = (function() {
  var cls = function IStorageFile() {
    this.contentType = new String();
    this.fileType = new String();
  };

  cls.prototype.openAsync = function openAsync(accessMode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="accessMode" type="FileAccessMode">A param.</param>
    /// </signature>
  };

  cls.prototype.openTransactedWriteAsync = function openTransactedWriteAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.copyAsync = function copyAsync(destinationFolder, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// </signature>
  };

  cls.prototype.copyAsync = function copyAsync(destinationFolder, desiredNewName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// <param name="desiredNewName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.copyAsync = function copyAsync(
    destinationFolder,
    desiredNewName,
    option,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// <param name="desiredNewName" type="String">A param.</param>
    /// <param name="option" type="NameCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.copyAndReplaceAsync = function copyAndReplaceAsync(fileToReplace, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="fileToReplace" type="IStorageFile">A param.</param>
    /// </signature>
  };

  cls.prototype.moveAsync = function moveAsync(destinationFolder, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// </signature>
  };

  cls.prototype.moveAsync = function moveAsync(destinationFolder, desiredNewName, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// <param name="desiredNewName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.moveAsync = function moveAsync(
    destinationFolder,
    desiredNewName,
    option,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationFolder" type="IStorageFolder">A param.</param>
    /// <param name="desiredNewName" type="String">A param.</param>
    /// <param name="option" type="NameCollisionOption">A param.</param>
    /// </signature>
  };

  cls.prototype.moveAndReplaceAsync = function moveAndReplaceAsync(fileToReplace, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="fileToReplace" type="IStorageFile">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.IStorageFile = IStorageFile;

IStorageItem2 = (function() {
  var cls = function IStorageItem2() {};

  cls.prototype.getParentAsync = function getParentAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.isEqual = function isEqual(item) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="item" type="IStorageItem">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  return cls;
})();
exports.IStorageItem2 = IStorageItem2;

IStorageItemProperties = (function() {
  var cls = function IStorageItemProperties() {
    this.displayName = new String();
    this.displayType = new String();
    this.folderRelativeId = new String();
    this.properties = new Object();
  };

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(mode, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(mode, requestedSize, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getThumbnailAsync = function getThumbnailAsync(
    mode,
    requestedSize,
    options,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// <param name="options" type="Number">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.IStorageItemProperties = IStorageItemProperties;

IStorageItemProperties2 = (function() {
  var cls = function IStorageItemProperties2() {};

  cls.prototype.getScaledImageAsThumbnailAsync = function getScaledImageAsThumbnailAsync(
    mode,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getScaledImageAsThumbnailAsync = function getScaledImageAsThumbnailAsync(
    mode,
    requestedSize,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// </signature>
  };

  cls.prototype.getScaledImageAsThumbnailAsync = function getScaledImageAsThumbnailAsync(
    mode,
    requestedSize,
    options,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mode" type="Number">A param.</param>
    /// <param name="requestedSize" type="Number">A param.</param>
    /// <param name="options" type="Number">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.IStorageItemProperties2 = IStorageItemProperties2;

IStorageItemPropertiesWithProvider = (function() {
  var cls = function IStorageItemPropertiesWithProvider() {
    this.provider = new StorageProvider();
  };

  return cls;
})();
exports.IStorageItemPropertiesWithProvider = IStorageItemPropertiesWithProvider;

StorageProvider = (function() {
  var cls = function StorageProvider() {
    this.displayName = new String();
    this.id = new String();
  };

  cls.prototype.isPropertySupportedForPartialFileAsync = function isPropertySupportedForPartialFileAsync(
    propertyCanonicalName,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="propertyCanonicalName" type="String">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.StorageProvider = StorageProvider;

IStorageFilePropertiesWithAvailability = (function() {
  var cls = function IStorageFilePropertiesWithAvailability() {
    this.isAvailable = new Boolean();
  };

  return cls;
})();
exports.IStorageFilePropertiesWithAvailability = IStorageFilePropertiesWithAvailability;

IStorageFolder2 = (function() {
  var cls = function IStorageFolder2() {};

  cls.prototype.tryGetItemAsync = function tryGetItemAsync(name, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.IStorageFolder2 = IStorageFolder2;

IStorageFile2 = (function() {
  var cls = function IStorageFile2() {};

  cls.prototype.openAsync = function openAsync(accessMode, options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="accessMode" type="FileAccessMode">A param.</param>
    /// <param name="options" type="StorageOpenOptions">A param.</param>
    /// </signature>
  };

  cls.prototype.openTransactedWriteAsync = function openTransactedWriteAsync(options, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="options" type="StorageOpenOptions">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.IStorageFile2 = IStorageFile2;

FileIO = (function() {
  var cls = function FileIO() {};

  cls.readTextAsync = function readTextAsync(file, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// </signature>
  };

  cls.readTextAsync = function readTextAsync(file, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.writeTextAsync = function writeTextAsync(file, contents, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="contents" type="String">A param.</param>
    /// </signature>
  };

  cls.writeTextAsync = function writeTextAsync(file, contents, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="contents" type="String">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.appendTextAsync = function appendTextAsync(file, contents, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="contents" type="String">A param.</param>
    /// </signature>
  };

  cls.appendTextAsync = function appendTextAsync(file, contents, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="contents" type="String">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.readLinesAsync = function readLinesAsync(file, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// </signature>
  };

  cls.readLinesAsync = function readLinesAsync(file, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.writeLinesAsync = function writeLinesAsync(file, lines, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="lines" type="Object">A param.</param>
    /// </signature>
  };

  cls.writeLinesAsync = function writeLinesAsync(file, lines, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="lines" type="Object">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.appendLinesAsync = function appendLinesAsync(file, lines, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="lines" type="Object">A param.</param>
    /// </signature>
  };

  cls.appendLinesAsync = function appendLinesAsync(file, lines, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="lines" type="Object">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.readBufferAsync = function readBufferAsync(file, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// </signature>
  };

  cls.writeBufferAsync = function writeBufferAsync(file, buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="buffer" type="Object">A param.</param>
    /// </signature>
  };

  cls.writeBytesAsync = function writeBytesAsync(file, buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// <param name="buffer" type="Array<Number>">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.FileIO = FileIO;

PathIO = (function() {
  var cls = function PathIO() {};

  cls.readTextAsync = function readTextAsync(absolutePath, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// </signature>
  };

  cls.readTextAsync = function readTextAsync(absolutePath, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.writeTextAsync = function writeTextAsync(absolutePath, contents, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="contents" type="String">A param.</param>
    /// </signature>
  };

  cls.writeTextAsync = function writeTextAsync(absolutePath, contents, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="contents" type="String">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.appendTextAsync = function appendTextAsync(absolutePath, contents, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="contents" type="String">A param.</param>
    /// </signature>
  };

  cls.appendTextAsync = function appendTextAsync(absolutePath, contents, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="contents" type="String">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.readLinesAsync = function readLinesAsync(absolutePath, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// </signature>
  };

  cls.readLinesAsync = function readLinesAsync(absolutePath, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.writeLinesAsync = function writeLinesAsync(absolutePath, lines, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="lines" type="Object">A param.</param>
    /// </signature>
  };

  cls.writeLinesAsync = function writeLinesAsync(absolutePath, lines, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="lines" type="Object">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.appendLinesAsync = function appendLinesAsync(absolutePath, lines, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="lines" type="Object">A param.</param>
    /// </signature>
  };

  cls.appendLinesAsync = function appendLinesAsync(absolutePath, lines, encoding, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="lines" type="Object">A param.</param>
    /// <param name="encoding" type="Number">A param.</param>
    /// </signature>
  };

  cls.readBufferAsync = function readBufferAsync(absolutePath, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// </signature>
  };

  cls.writeBufferAsync = function writeBufferAsync(absolutePath, buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="buffer" type="Object">A param.</param>
    /// </signature>
  };

  cls.writeBytesAsync = function writeBytesAsync(absolutePath, buffer, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="absolutePath" type="String">A param.</param>
    /// <param name="buffer" type="Array<Number>">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.PathIO = PathIO;

CachedFileManager = (function() {
  var cls = function CachedFileManager() {};

  cls.completeUpdatesAsync = function completeUpdatesAsync(file, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// </signature>
  };

  cls.deferUpdates = function deferUpdates(file) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="IStorageFile">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.CachedFileManager = CachedFileManager;

SystemAudioProperties = (function() {
  var cls = function SystemAudioProperties() {
    this.encodingBitrate = new String();
  };

  return cls;
})();
exports.SystemAudioProperties = SystemAudioProperties;

SystemGPSProperties = (function() {
  var cls = function SystemGPSProperties() {
    this.latitudeDecimal = new String();
    this.longitudeDecimal = new String();
  };

  return cls;
})();
exports.SystemGPSProperties = SystemGPSProperties;

SystemImageProperties = (function() {
  var cls = function SystemImageProperties() {
    this.horizontalSize = new String();
    this.verticalSize = new String();
  };

  return cls;
})();
exports.SystemImageProperties = SystemImageProperties;

SystemMediaProperties = (function() {
  var cls = function SystemMediaProperties() {
    this.duration = new String();
    this.producer = new String();
    this.publisher = new String();
    this.subTitle = new String();
    this.writer = new String();
    this.year = new String();
  };

  return cls;
})();
exports.SystemMediaProperties = SystemMediaProperties;

SystemMusicProperties = (function() {
  var cls = function SystemMusicProperties() {
    this.albumArtist = new String();
    this.albumTitle = new String();
    this.artist = new String();
    this.composer = new String();
    this.conductor = new String();
    this.displayArtist = new String();
    this.genre = new String();
    this.trackNumber = new String();
  };

  return cls;
})();
exports.SystemMusicProperties = SystemMusicProperties;

SystemPhotoProperties = (function() {
  var cls = function SystemPhotoProperties() {
    this.cameraManufacturer = new String();
    this.cameraModel = new String();
    this.dateTaken = new String();
    this.orientation = new String();
    this.peopleNames = new String();
  };

  return cls;
})();
exports.SystemPhotoProperties = SystemPhotoProperties;

SystemVideoProperties = (function() {
  var cls = function SystemVideoProperties() {
    this.director = new String();
    this.frameHeight = new String();
    this.frameWidth = new String();
    this.orientation = new String();
    this.totalBitrate = new String();
  };

  return cls;
})();
exports.SystemVideoProperties = SystemVideoProperties;

SystemProperties = (function() {
  var cls = function SystemProperties() {};

  cls.audio = new SystemAudioProperties();
  cls.author = new String();
  cls.comment = new String();
  cls.gPS = new SystemGPSProperties();
  cls.image = new SystemImageProperties();
  cls.itemNameDisplay = new String();
  cls.keywords = new String();
  cls.media = new SystemMediaProperties();
  cls.music = new SystemMusicProperties();
  cls.photo = new SystemPhotoProperties();
  cls.rating = new String();
  cls.title = new String();
  cls.video = new SystemVideoProperties();
  return cls;
})();
exports.SystemProperties = SystemProperties;

ApplicationData = (function() {
  var cls = function ApplicationData() {
    this.localFolder = new StorageFolder();
    this.localSettings = new ApplicationDataContainer();
    this.roamingFolder = new StorageFolder();
    this.roamingSettings = new ApplicationDataContainer();
    this.roamingStorageQuota = new Number();
    this.temporaryFolder = new StorageFolder();
    this.version = new Number();
    this.localCacheFolder = new StorageFolder();
    this.sharedLocalFolder = new StorageFolder();
  };

  cls.prototype.setVersionAsync = function setVersionAsync(desiredVersion, handler, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="desiredVersion" type="Number">A param.</param>
    /// <param name="handler" type="Object">A param.</param>
    /// </signature>
  };

  cls.prototype.clearAsync = function clearAsync(callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.clearAsync = function clearAsync(locality, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="locality" type="ApplicationDataLocality">A param.</param>
    /// </signature>
  };

  cls.prototype.clearPublisherCacheFolderAsync = function clearPublisherCacheFolderAsync(
    folderName,
    callback
  ) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="folderName" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.signalDataChanged = function signalDataChanged() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.getPublisherCacheFolder = function getPublisherCacheFolder(folderName) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="folderName" type="String">A param.</param>
    /// <returns type="StorageFolder" />
    /// </signature>
    return new StorageFolder();
  };

  cls.getForUserAsync = function getForUserAsync(user, callback) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// </signature>
  };

  cls.current = new ApplicationData();
  cls.prototype.addListener = function addListener(eventName, callback) {};
  cls.prototype.removeListener = function removeListener(eventName, callback) {};
  cls.prototype.on = function on(eventName, callback) {};
  cls.prototype.off = function off(eventName, callback) {};
  return cls;
})();
exports.ApplicationData = ApplicationData;

SetVersionRequest = (function() {
  var cls = function SetVersionRequest() {
    this.currentVersion = new Number();
    this.desiredVersion = new Number();
  };

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="SetVersionDeferral" />
    /// </signature>
    return new SetVersionDeferral();
  };

  return cls;
})();
exports.SetVersionRequest = SetVersionRequest;

ApplicationDataContainer = (function() {
  var cls = function ApplicationDataContainer() {
    this.containers = new Object();
    this.locality = new ApplicationDataLocality();
    this.name = new String();
    this.values = new Object();
  };

  cls.prototype.createContainer = function createContainer(name, disposition) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// <param name="disposition" type="ApplicationDataCreateDisposition">A param.</param>
    /// <returns type="ApplicationDataContainer" />
    /// </signature>
    return new ApplicationDataContainer();
  };

  cls.prototype.deleteContainer = function deleteContainer(name) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="name" type="String">A param.</param>
    /// </signature>
  };

  return cls;
})();
exports.ApplicationDataContainer = ApplicationDataContainer;

SetVersionDeferral = (function() {
  var cls = function SetVersionDeferral() {};

  cls.prototype.complete = function complete() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  return cls;
})();
exports.SetVersionDeferral = SetVersionDeferral;

ApplicationDataContainerSettings = (function() {
  var cls = function ApplicationDataContainerSettings() {};

  cls.prototype.lookup = function lookup(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.hasKey = function hasKey(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.prototype.getView = function getView() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.insert = function insert(key, value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <param name="value" type="Object">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.prototype.remove = function remove(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.clear = function clear() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.first = function first() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.addListener = function addListener(eventName, callback) {};
  cls.prototype.removeListener = function removeListener(eventName, callback) {};
  cls.prototype.on = function on(eventName, callback) {};
  cls.prototype.off = function off(eventName, callback) {};
  return cls;
})();
exports.ApplicationDataContainerSettings = ApplicationDataContainerSettings;

ApplicationDataCompositeValue = (function() {
  var cls = function ApplicationDataCompositeValue() {};

  cls.prototype.lookup = function lookup(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.hasKey = function hasKey(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.prototype.getView = function getView() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.insert = function insert(key, value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// <param name="value" type="Object">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  };

  cls.prototype.remove = function remove(key) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="key" type="String">A param.</param>
    /// </signature>
  };

  cls.prototype.clear = function clear() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  };

  cls.prototype.first = function first() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  };

  cls.prototype.addListener = function addListener(eventName, callback) {};
  cls.prototype.removeListener = function removeListener(eventName, callback) {};
  cls.prototype.on = function on(eventName, callback) {};
  cls.prototype.off = function off(eventName, callback) {};
  return cls;
})();
exports.ApplicationDataCompositeValue = ApplicationDataCompositeValue;
