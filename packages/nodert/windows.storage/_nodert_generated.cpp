// Copyright (c) The NodeRT Contributors
// All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may
// not use this file except in compliance with the License. You may obtain a
// copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS
// OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY
// IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
//
// See the Apache Version 2.0 License for specific language governing permissions
// and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace Storage { 
  v8::Local<v8::Value> WrapStorageLibrary(::Windows::Storage::StorageLibrary^ wintRtInstance);
  ::Windows::Storage::StorageLibrary^ UnwrapStorageLibrary(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorageFolder(::Windows::Storage::StorageFolder^ wintRtInstance);
  ::Windows::Storage::StorageFolder^ UnwrapStorageFolder(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorageLibraryChangeTracker(::Windows::Storage::StorageLibraryChangeTracker^ wintRtInstance);
  ::Windows::Storage::StorageLibraryChangeTracker^ UnwrapStorageLibraryChangeTracker(Local<Value> value);
  
  v8::Local<v8::Value> WrapKnownFolders(::Windows::Storage::KnownFolders^ wintRtInstance);
  ::Windows::Storage::KnownFolders^ UnwrapKnownFolders(Local<Value> value);
  
  v8::Local<v8::Value> WrapUserDataPaths(::Windows::Storage::UserDataPaths^ wintRtInstance);
  ::Windows::Storage::UserDataPaths^ UnwrapUserDataPaths(Local<Value> value);
  
  v8::Local<v8::Value> WrapAppDataPaths(::Windows::Storage::AppDataPaths^ wintRtInstance);
  ::Windows::Storage::AppDataPaths^ UnwrapAppDataPaths(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemDataPaths(::Windows::Storage::SystemDataPaths^ wintRtInstance);
  ::Windows::Storage::SystemDataPaths^ UnwrapSystemDataPaths(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorageFile(::Windows::Storage::StorageFile^ wintRtInstance);
  ::Windows::Storage::StorageFile^ UnwrapStorageFile(Local<Value> value);
  
  v8::Local<v8::Value> WrapDownloadsFolder(::Windows::Storage::DownloadsFolder^ wintRtInstance);
  ::Windows::Storage::DownloadsFolder^ UnwrapDownloadsFolder(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStorageItem(::Windows::Storage::IStorageItem^ wintRtInstance);
  ::Windows::Storage::IStorageItem^ UnwrapIStorageItem(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorageLibraryChange(::Windows::Storage::StorageLibraryChange^ wintRtInstance);
  ::Windows::Storage::StorageLibraryChange^ UnwrapStorageLibraryChange(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorageLibraryChangeReader(::Windows::Storage::StorageLibraryChangeReader^ wintRtInstance);
  ::Windows::Storage::StorageLibraryChangeReader^ UnwrapStorageLibraryChangeReader(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStreamedFileDataRequest(::Windows::Storage::IStreamedFileDataRequest^ wintRtInstance);
  ::Windows::Storage::IStreamedFileDataRequest^ UnwrapIStreamedFileDataRequest(Local<Value> value);
  
  v8::Local<v8::Value> WrapStreamedFileDataRequest(::Windows::Storage::StreamedFileDataRequest^ wintRtInstance);
  ::Windows::Storage::StreamedFileDataRequest^ UnwrapStreamedFileDataRequest(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorageStreamTransaction(::Windows::Storage::StorageStreamTransaction^ wintRtInstance);
  ::Windows::Storage::StorageStreamTransaction^ UnwrapStorageStreamTransaction(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStorageFolder(::Windows::Storage::IStorageFolder^ wintRtInstance);
  ::Windows::Storage::IStorageFolder^ UnwrapIStorageFolder(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStorageFile(::Windows::Storage::IStorageFile^ wintRtInstance);
  ::Windows::Storage::IStorageFile^ UnwrapIStorageFile(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStorageItem2(::Windows::Storage::IStorageItem2^ wintRtInstance);
  ::Windows::Storage::IStorageItem2^ UnwrapIStorageItem2(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStorageItemProperties(::Windows::Storage::IStorageItemProperties^ wintRtInstance);
  ::Windows::Storage::IStorageItemProperties^ UnwrapIStorageItemProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStorageItemProperties2(::Windows::Storage::IStorageItemProperties2^ wintRtInstance);
  ::Windows::Storage::IStorageItemProperties2^ UnwrapIStorageItemProperties2(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStorageItemPropertiesWithProvider(::Windows::Storage::IStorageItemPropertiesWithProvider^ wintRtInstance);
  ::Windows::Storage::IStorageItemPropertiesWithProvider^ UnwrapIStorageItemPropertiesWithProvider(Local<Value> value);
  
  v8::Local<v8::Value> WrapStorageProvider(::Windows::Storage::StorageProvider^ wintRtInstance);
  ::Windows::Storage::StorageProvider^ UnwrapStorageProvider(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStorageFilePropertiesWithAvailability(::Windows::Storage::IStorageFilePropertiesWithAvailability^ wintRtInstance);
  ::Windows::Storage::IStorageFilePropertiesWithAvailability^ UnwrapIStorageFilePropertiesWithAvailability(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStorageFolder2(::Windows::Storage::IStorageFolder2^ wintRtInstance);
  ::Windows::Storage::IStorageFolder2^ UnwrapIStorageFolder2(Local<Value> value);
  
  v8::Local<v8::Value> WrapIStorageFile2(::Windows::Storage::IStorageFile2^ wintRtInstance);
  ::Windows::Storage::IStorageFile2^ UnwrapIStorageFile2(Local<Value> value);
  
  v8::Local<v8::Value> WrapFileIO(::Windows::Storage::FileIO^ wintRtInstance);
  ::Windows::Storage::FileIO^ UnwrapFileIO(Local<Value> value);
  
  v8::Local<v8::Value> WrapPathIO(::Windows::Storage::PathIO^ wintRtInstance);
  ::Windows::Storage::PathIO^ UnwrapPathIO(Local<Value> value);
  
  v8::Local<v8::Value> WrapCachedFileManager(::Windows::Storage::CachedFileManager^ wintRtInstance);
  ::Windows::Storage::CachedFileManager^ UnwrapCachedFileManager(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemAudioProperties(::Windows::Storage::SystemAudioProperties^ wintRtInstance);
  ::Windows::Storage::SystemAudioProperties^ UnwrapSystemAudioProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemGPSProperties(::Windows::Storage::SystemGPSProperties^ wintRtInstance);
  ::Windows::Storage::SystemGPSProperties^ UnwrapSystemGPSProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemImageProperties(::Windows::Storage::SystemImageProperties^ wintRtInstance);
  ::Windows::Storage::SystemImageProperties^ UnwrapSystemImageProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemMediaProperties(::Windows::Storage::SystemMediaProperties^ wintRtInstance);
  ::Windows::Storage::SystemMediaProperties^ UnwrapSystemMediaProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemMusicProperties(::Windows::Storage::SystemMusicProperties^ wintRtInstance);
  ::Windows::Storage::SystemMusicProperties^ UnwrapSystemMusicProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemPhotoProperties(::Windows::Storage::SystemPhotoProperties^ wintRtInstance);
  ::Windows::Storage::SystemPhotoProperties^ UnwrapSystemPhotoProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemVideoProperties(::Windows::Storage::SystemVideoProperties^ wintRtInstance);
  ::Windows::Storage::SystemVideoProperties^ UnwrapSystemVideoProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapSystemProperties(::Windows::Storage::SystemProperties^ wintRtInstance);
  ::Windows::Storage::SystemProperties^ UnwrapSystemProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapApplicationData(::Windows::Storage::ApplicationData^ wintRtInstance);
  ::Windows::Storage::ApplicationData^ UnwrapApplicationData(Local<Value> value);
  
  v8::Local<v8::Value> WrapSetVersionRequest(::Windows::Storage::SetVersionRequest^ wintRtInstance);
  ::Windows::Storage::SetVersionRequest^ UnwrapSetVersionRequest(Local<Value> value);
  
  v8::Local<v8::Value> WrapApplicationDataContainer(::Windows::Storage::ApplicationDataContainer^ wintRtInstance);
  ::Windows::Storage::ApplicationDataContainer^ UnwrapApplicationDataContainer(Local<Value> value);
  
  v8::Local<v8::Value> WrapSetVersionDeferral(::Windows::Storage::SetVersionDeferral^ wintRtInstance);
  ::Windows::Storage::SetVersionDeferral^ UnwrapSetVersionDeferral(Local<Value> value);
  
  v8::Local<v8::Value> WrapApplicationDataContainerSettings(::Windows::Storage::ApplicationDataContainerSettings^ wintRtInstance);
  ::Windows::Storage::ApplicationDataContainerSettings^ UnwrapApplicationDataContainerSettings(Local<Value> value);
  
  v8::Local<v8::Value> WrapApplicationDataCompositeValue(::Windows::Storage::ApplicationDataCompositeValue^ wintRtInstance);
  ::Windows::Storage::ApplicationDataCompositeValue^ UnwrapApplicationDataCompositeValue(Local<Value> value);
  



  static void InitKnownLibraryIdEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("KnownLibraryId").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("music").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownLibraryId::Music)));
    Nan::Set(enumObject, Nan::New<String>("pictures").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownLibraryId::Pictures)));
    Nan::Set(enumObject, Nan::New<String>("videos").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownLibraryId::Videos)));
    Nan::Set(enumObject, Nan::New<String>("documents").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownLibraryId::Documents)));
  }

  static void InitKnownFolderIdEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("KnownFolderId").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("appCaptures").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::AppCaptures)));
    Nan::Set(enumObject, Nan::New<String>("cameraRoll").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::CameraRoll)));
    Nan::Set(enumObject, Nan::New<String>("documentsLibrary").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::DocumentsLibrary)));
    Nan::Set(enumObject, Nan::New<String>("homeGroup").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::HomeGroup)));
    Nan::Set(enumObject, Nan::New<String>("mediaServerDevices").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::MediaServerDevices)));
    Nan::Set(enumObject, Nan::New<String>("musicLibrary").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::MusicLibrary)));
    Nan::Set(enumObject, Nan::New<String>("objects3D").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::Objects3D)));
    Nan::Set(enumObject, Nan::New<String>("picturesLibrary").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::PicturesLibrary)));
    Nan::Set(enumObject, Nan::New<String>("playlists").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::Playlists)));
    Nan::Set(enumObject, Nan::New<String>("recordedCalls").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::RecordedCalls)));
    Nan::Set(enumObject, Nan::New<String>("removableDevices").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::RemovableDevices)));
    Nan::Set(enumObject, Nan::New<String>("savedPictures").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::SavedPictures)));
    Nan::Set(enumObject, Nan::New<String>("screenshots").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::Screenshots)));
    Nan::Set(enumObject, Nan::New<String>("videosLibrary").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::VideosLibrary)));
    Nan::Set(enumObject, Nan::New<String>("allAppMods").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::AllAppMods)));
    Nan::Set(enumObject, Nan::New<String>("currentAppMods").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::KnownFolderId::CurrentAppMods)));
  }

  static void InitCreationCollisionOptionEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("CreationCollisionOption").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("generateUniqueName").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::CreationCollisionOption::GenerateUniqueName)));
    Nan::Set(enumObject, Nan::New<String>("replaceExisting").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::CreationCollisionOption::ReplaceExisting)));
    Nan::Set(enumObject, Nan::New<String>("failIfExists").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::CreationCollisionOption::FailIfExists)));
    Nan::Set(enumObject, Nan::New<String>("openIfExists").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::CreationCollisionOption::OpenIfExists)));
  }

  static void InitNameCollisionOptionEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("NameCollisionOption").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("generateUniqueName").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::NameCollisionOption::GenerateUniqueName)));
    Nan::Set(enumObject, Nan::New<String>("replaceExisting").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::NameCollisionOption::ReplaceExisting)));
    Nan::Set(enumObject, Nan::New<String>("failIfExists").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::NameCollisionOption::FailIfExists)));
  }

  static void InitStorageDeleteOptionEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StorageDeleteOption").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("default").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageDeleteOption::Default)));
    Nan::Set(enumObject, Nan::New<String>("permanentDelete").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageDeleteOption::PermanentDelete)));
  }

  static void InitStorageItemTypesEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StorageItemTypes").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageItemTypes::None)));
    Nan::Set(enumObject, Nan::New<String>("file").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageItemTypes::File)));
    Nan::Set(enumObject, Nan::New<String>("folder").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageItemTypes::Folder)));
  }

  static void InitFileAttributesEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("FileAttributes").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("normal").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::FileAttributes::Normal)));
    Nan::Set(enumObject, Nan::New<String>("readOnly").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::FileAttributes::ReadOnly)));
    Nan::Set(enumObject, Nan::New<String>("directory").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::FileAttributes::Directory)));
    Nan::Set(enumObject, Nan::New<String>("archive").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::FileAttributes::Archive)));
    Nan::Set(enumObject, Nan::New<String>("temporary").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::FileAttributes::Temporary)));
    Nan::Set(enumObject, Nan::New<String>("locallyIncomplete").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::FileAttributes::LocallyIncomplete)));
  }

  static void InitFileAccessModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("FileAccessMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("read").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::FileAccessMode::Read)));
    Nan::Set(enumObject, Nan::New<String>("readWrite").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::FileAccessMode::ReadWrite)));
  }

  static void InitStorageLibraryChangeTypeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StorageLibraryChangeType").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("created").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageLibraryChangeType::Created)));
    Nan::Set(enumObject, Nan::New<String>("deleted").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageLibraryChangeType::Deleted)));
    Nan::Set(enumObject, Nan::New<String>("movedOrRenamed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageLibraryChangeType::MovedOrRenamed)));
    Nan::Set(enumObject, Nan::New<String>("contentsChanged").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageLibraryChangeType::ContentsChanged)));
    Nan::Set(enumObject, Nan::New<String>("movedOutOfLibrary").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageLibraryChangeType::MovedOutOfLibrary)));
    Nan::Set(enumObject, Nan::New<String>("movedIntoLibrary").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageLibraryChangeType::MovedIntoLibrary)));
    Nan::Set(enumObject, Nan::New<String>("contentsReplaced").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageLibraryChangeType::ContentsReplaced)));
    Nan::Set(enumObject, Nan::New<String>("indexingStatusChanged").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageLibraryChangeType::IndexingStatusChanged)));
    Nan::Set(enumObject, Nan::New<String>("encryptionChanged").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageLibraryChangeType::EncryptionChanged)));
    Nan::Set(enumObject, Nan::New<String>("changeTrackingLost").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageLibraryChangeType::ChangeTrackingLost)));
  }

  static void InitStreamedFileFailureModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StreamedFileFailureMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("failed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StreamedFileFailureMode::Failed)));
    Nan::Set(enumObject, Nan::New<String>("currentlyUnavailable").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StreamedFileFailureMode::CurrentlyUnavailable)));
    Nan::Set(enumObject, Nan::New<String>("incomplete").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StreamedFileFailureMode::Incomplete)));
  }

  static void InitStorageOpenOptionsEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StorageOpenOptions").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageOpenOptions::None)));
    Nan::Set(enumObject, Nan::New<String>("allowOnlyReaders").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageOpenOptions::AllowOnlyReaders)));
    Nan::Set(enumObject, Nan::New<String>("allowReadersAndWriters").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::StorageOpenOptions::AllowReadersAndWriters)));
  }

  static void InitApplicationDataLocalityEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("ApplicationDataLocality").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("local").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::ApplicationDataLocality::Local)));
    Nan::Set(enumObject, Nan::New<String>("roaming").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::ApplicationDataLocality::Roaming)));
    Nan::Set(enumObject, Nan::New<String>("temporary").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::ApplicationDataLocality::Temporary)));
    Nan::Set(enumObject, Nan::New<String>("localCache").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::ApplicationDataLocality::LocalCache)));
  }

  static void InitApplicationDataCreateDispositionEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("ApplicationDataCreateDisposition").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("always").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::ApplicationDataCreateDisposition::Always)));
    Nan::Set(enumObject, Nan::New<String>("existing").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Storage::ApplicationDataCreateDisposition::Existing)));
  }



  class StorageLibrary : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorageLibrary").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "requestAddFolderAsync", RequestAddFolderAsync);
            Nan::SetPrototypeMethod(localRef, "requestRemoveFolderAsync", RequestRemoveFolderAsync);
            Nan::SetPrototypeMethod(localRef, "areFolderSuggestionsAvailableAsync", AreFolderSuggestionsAvailableAsync);
          

          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("folders").ToLocalChecked(), FoldersGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("saveFolder").ToLocalChecked(), SaveFolderGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("changeTracker").ToLocalChecked(), ChangeTrackerGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetLibraryForUserAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("getLibraryForUserAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetLibraryAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("getLibraryAsync").ToLocalChecked(), func);


        Nan::Set(exports, Nan::New<String>("StorageLibrary").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorageLibrary(::Windows::Storage::StorageLibrary^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::StorageLibrary^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibrary^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::StorageLibrary^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorageLibrary *wrapperInstance = new StorageLibrary(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibrary^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::StorageLibrary^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::StorageLibrary^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorageLibrary(winRtInstance));
    }

    static void RequestAddFolderAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibrary^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageLibrary *wrapper = StorageLibrary::Unwrap<StorageLibrary>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->RequestAddFolderAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RequestRemoveFolderAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibrary^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageLibrary *wrapper = StorageLibrary::Unwrap<StorageLibrary>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info[0]))
      {
        try
        {
          ::Windows::Storage::StorageFolder^ arg0 = UnwrapStorageFolder(info[0]);
          
          op = wrapper->_instance->RequestRemoveFolderAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void AreFolderSuggestionsAvailableAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibrary^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageLibrary *wrapper = StorageLibrary::Unwrap<StorageLibrary>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->AreFolderSuggestionsAvailableAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }



    static void GetLibraryForUserAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageLibrary^>^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0])
          && info[1]->IsInt32())
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Storage::KnownLibraryId arg1 = static_cast<::Windows::Storage::KnownLibraryId>(Nan::To<int32_t>(info[1]).FromMaybe(0));
            
          op = ::Windows::Storage::StorageLibrary::GetLibraryForUserAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageLibrary^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageLibrary(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void GetLibraryAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageLibrary^>^ op;


      if (info.Length() == 2
          && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::KnownLibraryId arg0 = static_cast<::Windows::Storage::KnownLibraryId>(Nan::To<int32_t>(info[0]).FromMaybe(0));
            
          op = ::Windows::Storage::StorageLibrary::GetLibraryAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageLibrary^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageLibrary(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void FoldersGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibrary^>(info.This())) {
        return;
      }

      StorageLibrary *wrapper = StorageLibrary::Unwrap<StorageLibrary>(info.This());

      try  {
        ::Windows::Foundation::Collections::IObservableVector<::Windows::Storage::StorageFolder^>^ result = wrapper->_instance->Folders;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IObservableVector`1", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SaveFolderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibrary^>(info.This())) {
        return;
      }

      StorageLibrary *wrapper = StorageLibrary::Unwrap<StorageLibrary>(info.This());

      try  {
        ::Windows::Storage::StorageFolder^ result = wrapper->_instance->SaveFolder;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ChangeTrackerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibrary^>(info.This())) {
        return;
      }

      StorageLibrary *wrapper = StorageLibrary::Unwrap<StorageLibrary>(info.This());

      try  {
        ::Windows::Storage::StorageLibraryChangeTracker^ result = wrapper->_instance->ChangeTracker;
        info.GetReturnValue().Set(WrapStorageLibraryChangeTracker(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"definitionChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibrary^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        StorageLibrary *wrapper = StorageLibrary::Unwrap<StorageLibrary>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->DefinitionChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Storage::StorageLibrary^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Storage::StorageLibrary^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapStorageLibrary(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"definitionChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"definitionChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibrary^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          StorageLibrary *wrapper = StorageLibrary::Unwrap<StorageLibrary>(info.This());
          wrapper->_instance->DefinitionChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Storage::StorageLibrary^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorageLibrary(::Windows::Storage::StorageLibrary^ wintRtInstance);
      friend ::Windows::Storage::StorageLibrary^ UnwrapStorageLibrary(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorageLibrary::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorageLibrary(::Windows::Storage::StorageLibrary^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorageLibrary::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::StorageLibrary^ UnwrapStorageLibrary(Local<Value> value) {
     return StorageLibrary::Unwrap<StorageLibrary>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorageLibrary(Local<Object> exports) {
    StorageLibrary::Init(exports);
  }

  class StorageFolder : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorageFolder").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "tryGetChangeTracker", TryGetChangeTracker);
            Nan::SetPrototypeMethod(localRef, "isOfType", IsOfType);
            Nan::SetPrototypeMethod(localRef, "createFileQuery", CreateFileQuery);
            Nan::SetPrototypeMethod(localRef, "createFileQueryWithOptions", CreateFileQueryWithOptions);
            Nan::SetPrototypeMethod(localRef, "createFolderQuery", CreateFolderQuery);
            Nan::SetPrototypeMethod(localRef, "createFolderQueryWithOptions", CreateFolderQueryWithOptions);
            Nan::SetPrototypeMethod(localRef, "createItemQuery", CreateItemQuery);
            Nan::SetPrototypeMethod(localRef, "createItemQueryWithOptions", CreateItemQueryWithOptions);
            Nan::SetPrototypeMethod(localRef, "areQueryOptionsSupported", AreQueryOptionsSupported);
            Nan::SetPrototypeMethod(localRef, "isCommonFolderQuerySupported", IsCommonFolderQuerySupported);
            Nan::SetPrototypeMethod(localRef, "isCommonFileQuerySupported", IsCommonFileQuerySupported);
            Nan::SetPrototypeMethod(localRef, "isEqual", IsEqual);
          

          
            Nan::SetPrototypeMethod(localRef, "createFileAsync", CreateFileAsync);
            Nan::SetPrototypeMethod(localRef, "createFolderAsync", CreateFolderAsync);
            Nan::SetPrototypeMethod(localRef, "getFileAsync", GetFileAsync);
            Nan::SetPrototypeMethod(localRef, "getFolderAsync", GetFolderAsync);
            Nan::SetPrototypeMethod(localRef, "getItemAsync", GetItemAsync);
            Nan::SetPrototypeMethod(localRef, "getFilesAsync", GetFilesAsync);
            Nan::SetPrototypeMethod(localRef, "getFoldersAsync", GetFoldersAsync);
            Nan::SetPrototypeMethod(localRef, "getItemsAsync", GetItemsAsync);
            Nan::SetPrototypeMethod(localRef, "renameAsync", RenameAsync);
            Nan::SetPrototypeMethod(localRef, "deleteAsync", DeleteAsync);
            Nan::SetPrototypeMethod(localRef, "getBasicPropertiesAsync", GetBasicPropertiesAsync);
            Nan::SetPrototypeMethod(localRef, "getIndexedStateAsync", GetIndexedStateAsync);
            Nan::SetPrototypeMethod(localRef, "getThumbnailAsync", GetThumbnailAsync);
            Nan::SetPrototypeMethod(localRef, "getScaledImageAsThumbnailAsync", GetScaledImageAsThumbnailAsync);
            Nan::SetPrototypeMethod(localRef, "getParentAsync", GetParentAsync);
            Nan::SetPrototypeMethod(localRef, "tryGetItemAsync", TryGetItemAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dateCreated").ToLocalChecked(), DateCreatedGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("path").ToLocalChecked(), PathGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayType").ToLocalChecked(), DisplayTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("folderRelativeId").ToLocalChecked(), FolderRelativeIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("properties").ToLocalChecked(), PropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("provider").ToLocalChecked(), ProviderGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetFolderFromPathAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("getFolderFromPathAsync").ToLocalChecked(), func);


        Nan::Set(exports, Nan::New<String>("StorageFolder").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorageFolder(::Windows::Storage::StorageFolder^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::StorageFolder^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::StorageFolder^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorageFolder *wrapperInstance = new StorageFolder(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::StorageFolder^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::StorageFolder^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorageFolder(winRtInstance));
    }

    static void CreateFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->CreateFileAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::CreationCollisionOption arg1 = static_cast<::Windows::Storage::CreationCollisionOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->CreateFileAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void CreateFolderAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->CreateFolderAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::CreationCollisionOption arg1 = static_cast<::Windows::Storage::CreationCollisionOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->CreateFolderAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->GetFileAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetFolderAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->GetFolderAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetItemAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::IStorageItem^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->GetItemAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::IStorageItem^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIStorageItem(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetFilesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::StorageFile^>^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetFilesAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsUint32()
        && info[2]->IsUint32())
      {
        try
        {
          ::Windows::Storage::Search::CommonFileQuery arg0 = static_cast<::Windows::Storage::Search::CommonFileQuery>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          unsigned int arg2 = static_cast<unsigned int>(Nan::To<uint32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->GetFilesAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Search::CommonFileQuery arg0 = static_cast<::Windows::Storage::Search::CommonFileQuery>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetFilesAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::StorageFile^>^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Storage::StorageFile^>::CreateVectorViewWrapper(result, 
            [](::Windows::Storage::StorageFile^ val) -> Local<Value> {
              return WrapStorageFile(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(value);
            },
            [](Local<Value> value) -> ::Windows::Storage::StorageFile^ {
              return UnwrapStorageFile(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetFoldersAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::StorageFolder^>^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetFoldersAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsUint32()
        && info[2]->IsUint32())
      {
        try
        {
          ::Windows::Storage::Search::CommonFolderQuery arg0 = static_cast<::Windows::Storage::Search::CommonFolderQuery>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          unsigned int arg2 = static_cast<unsigned int>(Nan::To<uint32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->GetFoldersAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Search::CommonFolderQuery arg0 = static_cast<::Windows::Storage::Search::CommonFolderQuery>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetFoldersAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::StorageFolder^>^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Storage::StorageFolder^>::CreateVectorViewWrapper(result, 
            [](::Windows::Storage::StorageFolder^ val) -> Local<Value> {
              return WrapStorageFolder(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(value);
            },
            [](Local<Value> value) -> ::Windows::Storage::StorageFolder^ {
              return UnwrapStorageFolder(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetItemsAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::IStorageItem^>^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetItemsAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsUint32()
        && info[1]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetItemsAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::IStorageItem^>^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Storage::IStorageItem^>::CreateVectorViewWrapper(result, 
            [](::Windows::Storage::IStorageItem^ val) -> Local<Value> {
              return WrapIStorageItem(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(value);
            },
            [](Local<Value> value) -> ::Windows::Storage::IStorageItem^ {
              return UnwrapIStorageItem(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RenameAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->RenameAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::NameCollisionOption arg1 = static_cast<::Windows::Storage::NameCollisionOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->RenameAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void DeleteAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->DeleteAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StorageDeleteOption arg0 = static_cast<::Windows::Storage::StorageDeleteOption>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->DeleteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetBasicPropertiesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::FileProperties::BasicProperties^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetBasicPropertiesAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::FileProperties::BasicProperties^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "BasicProperties", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetIndexedStateAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Search::IndexedState>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetIndexedStateAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Search::IndexedState> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(static_cast<int>(result));
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::FileProperties::StorageItemThumbnail^>^ op;


      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetThumbnailAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsUint32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetThumbnailAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::FileProperties::ThumbnailOptions arg2 = static_cast<::Windows::Storage::FileProperties::ThumbnailOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->GetThumbnailAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::FileProperties::StorageItemThumbnail^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "StorageItemThumbnail", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetScaledImageAsThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::FileProperties::StorageItemThumbnail^>^ op;


      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetScaledImageAsThumbnailAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsUint32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetScaledImageAsThumbnailAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::FileProperties::ThumbnailOptions arg2 = static_cast<::Windows::Storage::FileProperties::ThumbnailOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->GetScaledImageAsThumbnailAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::FileProperties::StorageItemThumbnail^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "StorageItemThumbnail", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetParentAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetParentAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void TryGetItemAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::IStorageItem^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->TryGetItemAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::IStorageItem^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIStorageItem(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void TryGetChangeTracker(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::StorageLibraryChangeTracker^ result;
          result = wrapper->_instance->TryGetChangeTracker();
          info.GetReturnValue().Set(WrapStorageLibraryChangeTracker(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IsOfType(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StorageItemTypes arg0 = static_cast<::Windows::Storage::StorageItemTypes>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          bool result;
          result = wrapper->_instance->IsOfType(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateFileQuery(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Search::StorageFileQueryResult^ result;
          result = wrapper->_instance->CreateFileQuery();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Search", "StorageFileQueryResult", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Search::CommonFileQuery arg0 = static_cast<::Windows::Storage::Search::CommonFileQuery>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Search::StorageFileQueryResult^ result;
          result = wrapper->_instance->CreateFileQuery(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Search", "StorageFileQueryResult", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateFileQueryWithOptions(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Search::QueryOptions^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Search::QueryOptions^ arg0 = dynamic_cast<::Windows::Storage::Search::QueryOptions^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Storage::Search::StorageFileQueryResult^ result;
          result = wrapper->_instance->CreateFileQueryWithOptions(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Search", "StorageFileQueryResult", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateFolderQuery(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Search::StorageFolderQueryResult^ result;
          result = wrapper->_instance->CreateFolderQuery();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Search", "StorageFolderQueryResult", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Search::CommonFolderQuery arg0 = static_cast<::Windows::Storage::Search::CommonFolderQuery>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Search::StorageFolderQueryResult^ result;
          result = wrapper->_instance->CreateFolderQuery(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Search", "StorageFolderQueryResult", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateFolderQueryWithOptions(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Search::QueryOptions^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Search::QueryOptions^ arg0 = dynamic_cast<::Windows::Storage::Search::QueryOptions^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Storage::Search::StorageFolderQueryResult^ result;
          result = wrapper->_instance->CreateFolderQueryWithOptions(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Search", "StorageFolderQueryResult", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateItemQuery(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Search::StorageItemQueryResult^ result;
          result = wrapper->_instance->CreateItemQuery();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Search", "StorageItemQueryResult", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateItemQueryWithOptions(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Search::QueryOptions^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Search::QueryOptions^ arg0 = dynamic_cast<::Windows::Storage::Search::QueryOptions^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Storage::Search::StorageItemQueryResult^ result;
          result = wrapper->_instance->CreateItemQueryWithOptions(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Search", "StorageItemQueryResult", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AreQueryOptionsSupported(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Search::QueryOptions^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Search::QueryOptions^ arg0 = dynamic_cast<::Windows::Storage::Search::QueryOptions^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          bool result;
          result = wrapper->_instance->AreQueryOptionsSupported(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IsCommonFolderQuerySupported(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Search::CommonFolderQuery arg0 = static_cast<::Windows::Storage::Search::CommonFolderQuery>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          bool result;
          result = wrapper->_instance->IsCommonFolderQuerySupported(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IsCommonFileQuerySupported(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Search::CommonFileQuery arg0 = static_cast<::Windows::Storage::Search::CommonFileQuery>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          bool result;
          result = wrapper->_instance->IsCommonFileQuerySupported(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IsEqual(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageItem^ arg0 = UnwrapIStorageItem(info[0]);
          
          bool result;
          result = wrapper->_instance->IsEqual(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }


    static void GetFolderFromPathAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 2
          && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
            
          op = ::Windows::Storage::StorageFolder::GetFolderFromPathAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      try  {
        ::Windows::Storage::FileAttributes result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DateCreatedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      try  {
        ::Windows::Foundation::DateTime result = wrapper->_instance->DateCreated;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PathGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Path;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DisplayTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FolderRelativeIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FolderRelativeId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      try  {
        ::Windows::Storage::FileProperties::StorageItemContentProperties^ result = wrapper->_instance->Properties;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "StorageItemContentProperties", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProviderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(info.This())) {
        return;
      }

      StorageFolder *wrapper = StorageFolder::Unwrap<StorageFolder>(info.This());

      try  {
        ::Windows::Storage::StorageProvider^ result = wrapper->_instance->Provider;
        info.GetReturnValue().Set(WrapStorageProvider(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::StorageFolder^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorageFolder(::Windows::Storage::StorageFolder^ wintRtInstance);
      friend ::Windows::Storage::StorageFolder^ UnwrapStorageFolder(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorageFolder::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorageFolder(::Windows::Storage::StorageFolder^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorageFolder::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::StorageFolder^ UnwrapStorageFolder(Local<Value> value) {
     return StorageFolder::Unwrap<StorageFolder>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorageFolder(Local<Object> exports) {
    StorageFolder::Init(exports);
  }

  class StorageLibraryChangeTracker : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorageLibraryChangeTracker").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getChangeReader", GetChangeReader);
            Nan::SetPrototypeMethod(localRef, "enable", Enable);
            Nan::SetPrototypeMethod(localRef, "reset", Reset);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorageLibraryChangeTracker").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorageLibraryChangeTracker(::Windows::Storage::StorageLibraryChangeTracker^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::StorageLibraryChangeTracker^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChangeTracker^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::StorageLibraryChangeTracker^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorageLibraryChangeTracker *wrapperInstance = new StorageLibraryChangeTracker(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChangeTracker^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::StorageLibraryChangeTracker^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::StorageLibraryChangeTracker^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorageLibraryChangeTracker(winRtInstance));
    }


    static void GetChangeReader(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChangeTracker^>(info.This())) {
        return;
      }

      StorageLibraryChangeTracker *wrapper = StorageLibraryChangeTracker::Unwrap<StorageLibraryChangeTracker>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::StorageLibraryChangeReader^ result;
          result = wrapper->_instance->GetChangeReader();
          info.GetReturnValue().Set(WrapStorageLibraryChangeReader(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Enable(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChangeTracker^>(info.This())) {
        return;
      }

      StorageLibraryChangeTracker *wrapper = StorageLibraryChangeTracker::Unwrap<StorageLibraryChangeTracker>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Enable();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Reset(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChangeTracker^>(info.This())) {
        return;
      }

      StorageLibraryChangeTracker *wrapper = StorageLibraryChangeTracker::Unwrap<StorageLibraryChangeTracker>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Reset();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Storage::StorageLibraryChangeTracker^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorageLibraryChangeTracker(::Windows::Storage::StorageLibraryChangeTracker^ wintRtInstance);
      friend ::Windows::Storage::StorageLibraryChangeTracker^ UnwrapStorageLibraryChangeTracker(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorageLibraryChangeTracker::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorageLibraryChangeTracker(::Windows::Storage::StorageLibraryChangeTracker^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorageLibraryChangeTracker::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::StorageLibraryChangeTracker^ UnwrapStorageLibraryChangeTracker(Local<Value> value) {
     return StorageLibraryChangeTracker::Unwrap<StorageLibraryChangeTracker>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorageLibraryChangeTracker(Local<Object> exports) {
    StorageLibraryChangeTracker::Init(exports);
  }

  class KnownFolders : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("KnownFolders").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;





        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetFolderForUserAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("getFolderForUserAsync").ToLocalChecked(), func);
        Nan::SetAccessor(constructor, Nan::New<String>("cameraRoll").ToLocalChecked(), CameraRollGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("playlists").ToLocalChecked(), PlaylistsGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("savedPictures").ToLocalChecked(), SavedPicturesGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("documentsLibrary").ToLocalChecked(), DocumentsLibraryGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("homeGroup").ToLocalChecked(), HomeGroupGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mediaServerDevices").ToLocalChecked(), MediaServerDevicesGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("musicLibrary").ToLocalChecked(), MusicLibraryGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("picturesLibrary").ToLocalChecked(), PicturesLibraryGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("removableDevices").ToLocalChecked(), RemovableDevicesGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("videosLibrary").ToLocalChecked(), VideosLibraryGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("appCaptures").ToLocalChecked(), AppCapturesGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("objects3D").ToLocalChecked(), Objects3DGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("recordedCalls").ToLocalChecked(), RecordedCallsGetter);


        Nan::Set(exports, Nan::New<String>("KnownFolders").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      KnownFolders(::Windows::Storage::KnownFolders^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::KnownFolders^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::KnownFolders^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::KnownFolders^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      KnownFolders *wrapperInstance = new KnownFolders(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::KnownFolders^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::KnownFolders^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::KnownFolders^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapKnownFolders(winRtInstance));
    }




    static void GetFolderForUserAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0])
          && info[1]->IsInt32())
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Storage::KnownFolderId arg1 = static_cast<::Windows::Storage::KnownFolderId>(Nan::To<int32_t>(info[1]).FromMaybe(0));
            
          op = ::Windows::Storage::KnownFolders::GetFolderForUserAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    static void CameraRollGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::CameraRoll;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PlaylistsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::Playlists;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SavedPicturesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::SavedPictures;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void DocumentsLibraryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::DocumentsLibrary;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void HomeGroupGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::HomeGroup;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MediaServerDevicesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::MediaServerDevices;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MusicLibraryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::MusicLibrary;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PicturesLibraryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::PicturesLibrary;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void RemovableDevicesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::RemovableDevices;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void VideosLibraryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::VideosLibrary;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AppCapturesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::AppCaptures;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void Objects3DGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::Objects3D;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void RecordedCallsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::StorageFolder^ result = ::Windows::Storage::KnownFolders::RecordedCalls;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Storage::KnownFolders^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapKnownFolders(::Windows::Storage::KnownFolders^ wintRtInstance);
      friend ::Windows::Storage::KnownFolders^ UnwrapKnownFolders(Local<Value> value);
  };

  Persistent<FunctionTemplate> KnownFolders::s_constructorTemplate;

  v8::Local<v8::Value> WrapKnownFolders(::Windows::Storage::KnownFolders^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(KnownFolders::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::KnownFolders^ UnwrapKnownFolders(Local<Value> value) {
     return KnownFolders::Unwrap<KnownFolders>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitKnownFolders(Local<Object> exports) {
    KnownFolders::Init(exports);
  }

  class UserDataPaths : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("UserDataPaths").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("cameraRoll").ToLocalChecked(), CameraRollGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("cookies").ToLocalChecked(), CookiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("desktop").ToLocalChecked(), DesktopGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("documents").ToLocalChecked(), DocumentsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("downloads").ToLocalChecked(), DownloadsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("favorites").ToLocalChecked(), FavoritesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("history").ToLocalChecked(), HistoryGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("internetCache").ToLocalChecked(), InternetCacheGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localAppData").ToLocalChecked(), LocalAppDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localAppDataLow").ToLocalChecked(), LocalAppDataLowGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("music").ToLocalChecked(), MusicGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pictures").ToLocalChecked(), PicturesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("profile").ToLocalChecked(), ProfileGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("recent").ToLocalChecked(), RecentGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("roamingAppData").ToLocalChecked(), RoamingAppDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("savedPictures").ToLocalChecked(), SavedPicturesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("screenshots").ToLocalChecked(), ScreenshotsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("templates").ToLocalChecked(), TemplatesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("videos").ToLocalChecked(), VideosGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "getForUser", GetForUser);
        Nan::SetMethod(constructor, "getDefault", GetDefault);


        Nan::Set(exports, Nan::New<String>("UserDataPaths").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      UserDataPaths(::Windows::Storage::UserDataPaths^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::UserDataPaths^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::UserDataPaths^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      UserDataPaths *wrapperInstance = new UserDataPaths(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::UserDataPaths^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::UserDataPaths^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapUserDataPaths(winRtInstance));
    }





    static void GetForUser(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0]))
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Storage::UserDataPaths^ result;
          result = ::Windows::Storage::UserDataPaths::GetForUser(arg0);
          info.GetReturnValue().Set(WrapUserDataPaths(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void GetDefault(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::UserDataPaths^ result;
          result = ::Windows::Storage::UserDataPaths::GetDefault();
          info.GetReturnValue().Set(WrapUserDataPaths(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void CameraRollGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->CameraRoll;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CookiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Cookies;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DesktopGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Desktop;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DocumentsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Documents;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DownloadsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Downloads;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FavoritesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Favorites;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HistoryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->History;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InternetCacheGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InternetCache;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalAppDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->LocalAppData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalAppDataLowGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->LocalAppDataLow;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MusicGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Music;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PicturesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Pictures;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProfileGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Profile;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RecentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Recent;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RoamingAppDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->RoamingAppData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SavedPicturesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->SavedPictures;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ScreenshotsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Screenshots;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TemplatesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Templates;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void VideosGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::UserDataPaths^>(info.This())) {
        return;
      }

      UserDataPaths *wrapper = UserDataPaths::Unwrap<UserDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Videos;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::UserDataPaths^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapUserDataPaths(::Windows::Storage::UserDataPaths^ wintRtInstance);
      friend ::Windows::Storage::UserDataPaths^ UnwrapUserDataPaths(Local<Value> value);
  };

  Persistent<FunctionTemplate> UserDataPaths::s_constructorTemplate;

  v8::Local<v8::Value> WrapUserDataPaths(::Windows::Storage::UserDataPaths^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(UserDataPaths::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::UserDataPaths^ UnwrapUserDataPaths(Local<Value> value) {
     return UserDataPaths::Unwrap<UserDataPaths>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitUserDataPaths(Local<Object> exports) {
    UserDataPaths::Init(exports);
  }

  class AppDataPaths : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("AppDataPaths").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("cookies").ToLocalChecked(), CookiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("desktop").ToLocalChecked(), DesktopGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("documents").ToLocalChecked(), DocumentsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("favorites").ToLocalChecked(), FavoritesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("history").ToLocalChecked(), HistoryGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("internetCache").ToLocalChecked(), InternetCacheGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localAppData").ToLocalChecked(), LocalAppDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("programData").ToLocalChecked(), ProgramDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("roamingAppData").ToLocalChecked(), RoamingAppDataGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "getForUser", GetForUser);
        Nan::SetMethod(constructor, "getDefault", GetDefault);


        Nan::Set(exports, Nan::New<String>("AppDataPaths").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      AppDataPaths(::Windows::Storage::AppDataPaths^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::AppDataPaths^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::AppDataPaths^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      AppDataPaths *wrapperInstance = new AppDataPaths(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::AppDataPaths^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::AppDataPaths^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapAppDataPaths(winRtInstance));
    }





    static void GetForUser(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0]))
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Storage::AppDataPaths^ result;
          result = ::Windows::Storage::AppDataPaths::GetForUser(arg0);
          info.GetReturnValue().Set(WrapAppDataPaths(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void GetDefault(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::AppDataPaths^ result;
          result = ::Windows::Storage::AppDataPaths::GetDefault();
          info.GetReturnValue().Set(WrapAppDataPaths(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void CookiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info.This())) {
        return;
      }

      AppDataPaths *wrapper = AppDataPaths::Unwrap<AppDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Cookies;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DesktopGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info.This())) {
        return;
      }

      AppDataPaths *wrapper = AppDataPaths::Unwrap<AppDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Desktop;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DocumentsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info.This())) {
        return;
      }

      AppDataPaths *wrapper = AppDataPaths::Unwrap<AppDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Documents;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FavoritesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info.This())) {
        return;
      }

      AppDataPaths *wrapper = AppDataPaths::Unwrap<AppDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Favorites;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HistoryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info.This())) {
        return;
      }

      AppDataPaths *wrapper = AppDataPaths::Unwrap<AppDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->History;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InternetCacheGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info.This())) {
        return;
      }

      AppDataPaths *wrapper = AppDataPaths::Unwrap<AppDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->InternetCache;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalAppDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info.This())) {
        return;
      }

      AppDataPaths *wrapper = AppDataPaths::Unwrap<AppDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->LocalAppData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProgramDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info.This())) {
        return;
      }

      AppDataPaths *wrapper = AppDataPaths::Unwrap<AppDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ProgramData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RoamingAppDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::AppDataPaths^>(info.This())) {
        return;
      }

      AppDataPaths *wrapper = AppDataPaths::Unwrap<AppDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->RoamingAppData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::AppDataPaths^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapAppDataPaths(::Windows::Storage::AppDataPaths^ wintRtInstance);
      friend ::Windows::Storage::AppDataPaths^ UnwrapAppDataPaths(Local<Value> value);
  };

  Persistent<FunctionTemplate> AppDataPaths::s_constructorTemplate;

  v8::Local<v8::Value> WrapAppDataPaths(::Windows::Storage::AppDataPaths^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(AppDataPaths::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::AppDataPaths^ UnwrapAppDataPaths(Local<Value> value) {
     return AppDataPaths::Unwrap<AppDataPaths>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitAppDataPaths(Local<Object> exports) {
    AppDataPaths::Init(exports);
  }

  class SystemDataPaths : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemDataPaths").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("fonts").ToLocalChecked(), FontsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("programData").ToLocalChecked(), ProgramDataGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("public").ToLocalChecked(), PublicGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publicDesktop").ToLocalChecked(), PublicDesktopGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publicDocuments").ToLocalChecked(), PublicDocumentsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publicDownloads").ToLocalChecked(), PublicDownloadsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publicMusic").ToLocalChecked(), PublicMusicGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publicPictures").ToLocalChecked(), PublicPicturesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publicVideos").ToLocalChecked(), PublicVideosGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("system").ToLocalChecked(), SystemGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemArm").ToLocalChecked(), SystemArmGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemHost").ToLocalChecked(), SystemHostGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemX64").ToLocalChecked(), SystemX64Getter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemX86").ToLocalChecked(), SystemX86Getter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userProfiles").ToLocalChecked(), UserProfilesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("windows").ToLocalChecked(), WindowsGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "getDefault", GetDefault);


        Nan::Set(exports, Nan::New<String>("SystemDataPaths").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemDataPaths(::Windows::Storage::SystemDataPaths^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SystemDataPaths^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SystemDataPaths^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemDataPaths *wrapperInstance = new SystemDataPaths(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SystemDataPaths^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SystemDataPaths^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemDataPaths(winRtInstance));
    }





    static void GetDefault(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::SystemDataPaths^ result;
          result = ::Windows::Storage::SystemDataPaths::GetDefault();
          info.GetReturnValue().Set(WrapSystemDataPaths(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void FontsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Fonts;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProgramDataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ProgramData;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PublicGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Public;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PublicDesktopGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->PublicDesktop;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PublicDocumentsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->PublicDocuments;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PublicDownloadsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->PublicDownloads;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PublicMusicGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->PublicMusic;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PublicPicturesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->PublicPictures;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PublicVideosGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->PublicVideos;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SystemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->System;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SystemArmGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->SystemArm;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SystemHostGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->SystemHost;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SystemX64Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->SystemX64;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SystemX86Getter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->SystemX86;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void UserProfilesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->UserProfiles;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void WindowsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemDataPaths^>(info.This())) {
        return;
      }

      SystemDataPaths *wrapper = SystemDataPaths::Unwrap<SystemDataPaths>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Windows;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::SystemDataPaths^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemDataPaths(::Windows::Storage::SystemDataPaths^ wintRtInstance);
      friend ::Windows::Storage::SystemDataPaths^ UnwrapSystemDataPaths(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemDataPaths::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemDataPaths(::Windows::Storage::SystemDataPaths^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemDataPaths::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SystemDataPaths^ UnwrapSystemDataPaths(Local<Value> value) {
     return SystemDataPaths::Unwrap<SystemDataPaths>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemDataPaths(Local<Object> exports) {
    SystemDataPaths::Init(exports);
  }

  class StorageFile : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorageFile").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "isOfType", IsOfType);
            Nan::SetPrototypeMethod(localRef, "isEqual", IsEqual);
          

          
            Nan::SetPrototypeMethod(localRef, "openAsync", OpenAsync);
            Nan::SetPrototypeMethod(localRef, "openTransactedWriteAsync", OpenTransactedWriteAsync);
            Nan::SetPrototypeMethod(localRef, "copyAsync", CopyAsync);
            Nan::SetPrototypeMethod(localRef, "copyAndReplaceAsync", CopyAndReplaceAsync);
            Nan::SetPrototypeMethod(localRef, "moveAsync", MoveAsync);
            Nan::SetPrototypeMethod(localRef, "moveAndReplaceAsync", MoveAndReplaceAsync);
            Nan::SetPrototypeMethod(localRef, "renameAsync", RenameAsync);
            Nan::SetPrototypeMethod(localRef, "deleteAsync", DeleteAsync);
            Nan::SetPrototypeMethod(localRef, "getBasicPropertiesAsync", GetBasicPropertiesAsync);
            Nan::SetPrototypeMethod(localRef, "openReadAsync", OpenReadAsync);
            Nan::SetPrototypeMethod(localRef, "openSequentialReadAsync", OpenSequentialReadAsync);
            Nan::SetPrototypeMethod(localRef, "getThumbnailAsync", GetThumbnailAsync);
            Nan::SetPrototypeMethod(localRef, "getScaledImageAsThumbnailAsync", GetScaledImageAsThumbnailAsync);
            Nan::SetPrototypeMethod(localRef, "getParentAsync", GetParentAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("contentType").ToLocalChecked(), ContentTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("fileType").ToLocalChecked(), FileTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isAvailable").ToLocalChecked(), IsAvailableGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dateCreated").ToLocalChecked(), DateCreatedGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("path").ToLocalChecked(), PathGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayType").ToLocalChecked(), DisplayTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("folderRelativeId").ToLocalChecked(), FolderRelativeIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("properties").ToLocalChecked(), PropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("provider").ToLocalChecked(), ProviderGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetFileFromPathAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("getFileFromPathAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetFileFromApplicationUriAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("getFileFromApplicationUriAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateStreamedFileAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createStreamedFileAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(ReplaceWithStreamedFileAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("replaceWithStreamedFileAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateStreamedFileFromUriAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createStreamedFileFromUriAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(ReplaceWithStreamedFileFromUriAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("replaceWithStreamedFileFromUriAsync").ToLocalChecked(), func);


        Nan::Set(exports, Nan::New<String>("StorageFile").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorageFile(::Windows::Storage::StorageFile^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::StorageFile^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::StorageFile^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorageFile *wrapperInstance = new StorageFile(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::StorageFile^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::StorageFile^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorageFile(winRtInstance));
    }

    static void OpenAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IRandomAccessStream^>^ op;


      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileAccessMode arg0 = static_cast<::Windows::Storage::FileAccessMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->OpenAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileAccessMode arg0 = static_cast<::Windows::Storage::FileAccessMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Storage::StorageOpenOptions arg1 = static_cast<::Windows::Storage::StorageOpenOptions>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->OpenAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IRandomAccessStream^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IRandomAccessStream", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void OpenTransactedWriteAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageStreamTransaction^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->OpenTransactedWriteAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StorageOpenOptions arg0 = static_cast<::Windows::Storage::StorageOpenOptions>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->OpenTransactedWriteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageStreamTransaction^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageStreamTransaction(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void CopyAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          
          op = wrapper->_instance->CopyAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          op = wrapper->_instance->CopyAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0])
        && info[1]->IsString()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Storage::NameCollisionOption arg2 = static_cast<::Windows::Storage::NameCollisionOption>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->CopyAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void CopyAndReplaceAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          
          op = wrapper->_instance->CopyAndReplaceAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void MoveAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          
          op = wrapper->_instance->MoveAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          op = wrapper->_instance->MoveAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0])
        && info[1]->IsString()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Storage::NameCollisionOption arg2 = static_cast<::Windows::Storage::NameCollisionOption>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->MoveAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void MoveAndReplaceAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          
          op = wrapper->_instance->MoveAndReplaceAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void RenameAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->RenameAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::NameCollisionOption arg1 = static_cast<::Windows::Storage::NameCollisionOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->RenameAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void DeleteAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->DeleteAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StorageDeleteOption arg0 = static_cast<::Windows::Storage::StorageDeleteOption>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->DeleteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetBasicPropertiesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::FileProperties::BasicProperties^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetBasicPropertiesAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::FileProperties::BasicProperties^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "BasicProperties", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void OpenReadAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IRandomAccessStreamWithContentType^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->OpenReadAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IRandomAccessStreamWithContentType^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IRandomAccessStreamWithContentType", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void OpenSequentialReadAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IInputStream^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->OpenSequentialReadAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IInputStream^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IInputStream", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::FileProperties::StorageItemThumbnail^>^ op;


      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetThumbnailAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsUint32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetThumbnailAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::FileProperties::ThumbnailOptions arg2 = static_cast<::Windows::Storage::FileProperties::ThumbnailOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->GetThumbnailAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::FileProperties::StorageItemThumbnail^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "StorageItemThumbnail", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetScaledImageAsThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::FileProperties::StorageItemThumbnail^>^ op;


      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetScaledImageAsThumbnailAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsUint32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetScaledImageAsThumbnailAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::FileProperties::ThumbnailOptions arg2 = static_cast<::Windows::Storage::FileProperties::ThumbnailOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->GetScaledImageAsThumbnailAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::FileProperties::StorageItemThumbnail^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "StorageItemThumbnail", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetParentAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetParentAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void IsOfType(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StorageItemTypes arg0 = static_cast<::Windows::Storage::StorageItemTypes>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          bool result;
          result = wrapper->_instance->IsOfType(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IsEqual(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageItem^ arg0 = UnwrapIStorageItem(info[0]);
          
          bool result;
          result = wrapper->_instance->IsEqual(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }


    static void GetFileFromPathAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 2
          && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
            
          op = ::Windows::Storage::StorageFile::GetFileFromPathAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void GetFileFromApplicationUriAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
            
          op = ::Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void CreateStreamedFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 4
          && info[0]->IsString()
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StreamedFileDataRequestedHandler^>(info[1])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStreamReference^>(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::StreamedFileDataRequestedHandler^ arg1 = dynamic_cast<::Windows::Storage::StreamedFileDataRequestedHandler^>(NodeRT::Utils::GetObjectInstance(info[1]));
          ::Windows::Storage::Streams::IRandomAccessStreamReference^ arg2 = dynamic_cast<::Windows::Storage::Streams::IRandomAccessStreamReference^>(NodeRT::Utils::GetObjectInstance(info[2]));
            
          op = ::Windows::Storage::StorageFile::CreateStreamedFileAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void ReplaceWithStreamedFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 4
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StreamedFileDataRequestedHandler^>(info[1])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStreamReference^>(info[2]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          ::Windows::Storage::StreamedFileDataRequestedHandler^ arg1 = dynamic_cast<::Windows::Storage::StreamedFileDataRequestedHandler^>(NodeRT::Utils::GetObjectInstance(info[1]));
          ::Windows::Storage::Streams::IRandomAccessStreamReference^ arg2 = dynamic_cast<::Windows::Storage::Streams::IRandomAccessStreamReference^>(NodeRT::Utils::GetObjectInstance(info[2]));
            
          op = ::Windows::Storage::StorageFile::ReplaceWithStreamedFileAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void CreateStreamedFileFromUriAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 4
          && info[0]->IsString()
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[1])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStreamReference^>(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Uri^ arg1 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[1]));
          ::Windows::Storage::Streams::IRandomAccessStreamReference^ arg2 = dynamic_cast<::Windows::Storage::Streams::IRandomAccessStreamReference^>(NodeRT::Utils::GetObjectInstance(info[2]));
            
          op = ::Windows::Storage::StorageFile::CreateStreamedFileFromUriAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void ReplaceWithStreamedFileFromUriAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 4
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[1])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStreamReference^>(info[2]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          ::Windows::Foundation::Uri^ arg1 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[1]));
          ::Windows::Storage::Streams::IRandomAccessStreamReference^ arg2 = dynamic_cast<::Windows::Storage::Streams::IRandomAccessStreamReference^>(NodeRT::Utils::GetObjectInstance(info[2]));
            
          op = ::Windows::Storage::StorageFile::ReplaceWithStreamedFileFromUriAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void ContentTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ContentType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FileTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FileType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsAvailableGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        bool result = wrapper->_instance->IsAvailable;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        ::Windows::Storage::FileAttributes result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DateCreatedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        ::Windows::Foundation::DateTime result = wrapper->_instance->DateCreated;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PathGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Path;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DisplayTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FolderRelativeIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FolderRelativeId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        ::Windows::Storage::FileProperties::StorageItemContentProperties^ result = wrapper->_instance->Properties;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "StorageItemContentProperties", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProviderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(info.This())) {
        return;
      }

      StorageFile *wrapper = StorageFile::Unwrap<StorageFile>(info.This());

      try  {
        ::Windows::Storage::StorageProvider^ result = wrapper->_instance->Provider;
        info.GetReturnValue().Set(WrapStorageProvider(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::StorageFile^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorageFile(::Windows::Storage::StorageFile^ wintRtInstance);
      friend ::Windows::Storage::StorageFile^ UnwrapStorageFile(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorageFile::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorageFile(::Windows::Storage::StorageFile^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorageFile::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::StorageFile^ UnwrapStorageFile(Local<Value> value) {
     return StorageFile::Unwrap<StorageFile>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorageFile(Local<Object> exports) {
    StorageFile::Init(exports);
  }

  class DownloadsFolder : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("DownloadsFolder").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;





        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateFileForUserAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createFileForUserAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateFolderForUserAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createFolderForUserAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateFileAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createFileAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateFolderAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createFolderAsync").ToLocalChecked(), func);


        Nan::Set(exports, Nan::New<String>("DownloadsFolder").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      DownloadsFolder(::Windows::Storage::DownloadsFolder^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::DownloadsFolder^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::DownloadsFolder^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::DownloadsFolder^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      DownloadsFolder *wrapperInstance = new DownloadsFolder(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::DownloadsFolder^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::DownloadsFolder^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::DownloadsFolder^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapDownloadsFolder(winRtInstance));
    }




    static void CreateFileForUserAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0])
          && info[1]->IsString())
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
            
          op = ::Windows::Storage::DownloadsFolder::CreateFileForUserAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0])
          && info[1]->IsString()
          && info[2]->IsInt32())
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Storage::CreationCollisionOption arg2 = static_cast<::Windows::Storage::CreationCollisionOption>(Nan::To<int32_t>(info[2]).FromMaybe(0));
            
          op = ::Windows::Storage::DownloadsFolder::CreateFileForUserAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void CreateFolderForUserAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0])
          && info[1]->IsString())
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
            
          op = ::Windows::Storage::DownloadsFolder::CreateFolderForUserAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0])
          && info[1]->IsString()
          && info[2]->IsInt32())
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Storage::CreationCollisionOption arg2 = static_cast<::Windows::Storage::CreationCollisionOption>(Nan::To<int32_t>(info[2]).FromMaybe(0));
            
          op = ::Windows::Storage::DownloadsFolder::CreateFolderForUserAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void CreateFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 2
          && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
            
          op = ::Windows::Storage::DownloadsFolder::CreateFileAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 3
          && info[0]->IsString()
          && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::CreationCollisionOption arg1 = static_cast<::Windows::Storage::CreationCollisionOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
            
          op = ::Windows::Storage::DownloadsFolder::CreateFileAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void CreateFolderAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 2
          && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
            
          op = ::Windows::Storage::DownloadsFolder::CreateFolderAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 3
          && info[0]->IsString()
          && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::CreationCollisionOption arg1 = static_cast<::Windows::Storage::CreationCollisionOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
            
          op = ::Windows::Storage::DownloadsFolder::CreateFolderAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    private:
      ::Windows::Storage::DownloadsFolder^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapDownloadsFolder(::Windows::Storage::DownloadsFolder^ wintRtInstance);
      friend ::Windows::Storage::DownloadsFolder^ UnwrapDownloadsFolder(Local<Value> value);
  };

  Persistent<FunctionTemplate> DownloadsFolder::s_constructorTemplate;

  v8::Local<v8::Value> WrapDownloadsFolder(::Windows::Storage::DownloadsFolder^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(DownloadsFolder::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::DownloadsFolder^ UnwrapDownloadsFolder(Local<Value> value) {
     return DownloadsFolder::Unwrap<DownloadsFolder>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitDownloadsFolder(Local<Object> exports) {
    DownloadsFolder::Init(exports);
  }

  class IStorageItem : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStorageItem").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "isOfType", IsOfType);
          

          
            Nan::SetPrototypeMethod(localRef, "renameAsync", RenameAsync);
            Nan::SetPrototypeMethod(localRef, "deleteAsync", DeleteAsync);
            Nan::SetPrototypeMethod(localRef, "getBasicPropertiesAsync", GetBasicPropertiesAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("attributes").ToLocalChecked(), AttributesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dateCreated").ToLocalChecked(), DateCreatedGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("path").ToLocalChecked(), PathGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStorageItem").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStorageItem(::Windows::Storage::IStorageItem^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStorageItem^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStorageItem^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStorageItem *wrapperInstance = new IStorageItem(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStorageItem^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStorageItem^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStorageItem(winRtInstance));
    }

    static void RenameAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageItem *wrapper = IStorageItem::Unwrap<IStorageItem>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->RenameAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::NameCollisionOption arg1 = static_cast<::Windows::Storage::NameCollisionOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->RenameAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void DeleteAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageItem *wrapper = IStorageItem::Unwrap<IStorageItem>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->DeleteAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StorageDeleteOption arg0 = static_cast<::Windows::Storage::StorageDeleteOption>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->DeleteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetBasicPropertiesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageItem *wrapper = IStorageItem::Unwrap<IStorageItem>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::FileProperties::BasicProperties^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetBasicPropertiesAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::FileProperties::BasicProperties^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "BasicProperties", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void IsOfType(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info.This())) {
        return;
      }

      IStorageItem *wrapper = IStorageItem::Unwrap<IStorageItem>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StorageItemTypes arg0 = static_cast<::Windows::Storage::StorageItemTypes>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          bool result;
          result = wrapper->_instance->IsOfType(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void AttributesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info.This())) {
        return;
      }

      IStorageItem *wrapper = IStorageItem::Unwrap<IStorageItem>(info.This());

      try  {
        ::Windows::Storage::FileAttributes result = wrapper->_instance->Attributes;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DateCreatedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info.This())) {
        return;
      }

      IStorageItem *wrapper = IStorageItem::Unwrap<IStorageItem>(info.This());

      try  {
        ::Windows::Foundation::DateTime result = wrapper->_instance->DateCreated;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info.This())) {
        return;
      }

      IStorageItem *wrapper = IStorageItem::Unwrap<IStorageItem>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PathGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info.This())) {
        return;
      }

      IStorageItem *wrapper = IStorageItem::Unwrap<IStorageItem>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Path;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::IStorageItem^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStorageItem(::Windows::Storage::IStorageItem^ wintRtInstance);
      friend ::Windows::Storage::IStorageItem^ UnwrapIStorageItem(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStorageItem::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStorageItem(::Windows::Storage::IStorageItem^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStorageItem::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStorageItem^ UnwrapIStorageItem(Local<Value> value) {
     return IStorageItem::Unwrap<IStorageItem>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStorageItem(Local<Object> exports) {
    IStorageItem::Init(exports);
  }

  class StorageLibraryChange : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorageLibraryChange").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "isOfType", IsOfType);
          

          
            Nan::SetPrototypeMethod(localRef, "getStorageItemAsync", GetStorageItemAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("changeType").ToLocalChecked(), ChangeTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("path").ToLocalChecked(), PathGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousPath").ToLocalChecked(), PreviousPathGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorageLibraryChange").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorageLibraryChange(::Windows::Storage::StorageLibraryChange^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::StorageLibraryChange^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChange^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::StorageLibraryChange^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorageLibraryChange *wrapperInstance = new StorageLibraryChange(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChange^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::StorageLibraryChange^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::StorageLibraryChange^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorageLibraryChange(winRtInstance));
    }

    static void GetStorageItemAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChange^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageLibraryChange *wrapper = StorageLibraryChange::Unwrap<StorageLibraryChange>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::IStorageItem^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetStorageItemAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::IStorageItem^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIStorageItem(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void IsOfType(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChange^>(info.This())) {
        return;
      }

      StorageLibraryChange *wrapper = StorageLibraryChange::Unwrap<StorageLibraryChange>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StorageItemTypes arg0 = static_cast<::Windows::Storage::StorageItemTypes>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          bool result;
          result = wrapper->_instance->IsOfType(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void ChangeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChange^>(info.This())) {
        return;
      }

      StorageLibraryChange *wrapper = StorageLibraryChange::Unwrap<StorageLibraryChange>(info.This());

      try  {
        ::Windows::Storage::StorageLibraryChangeType result = wrapper->_instance->ChangeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PathGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChange^>(info.This())) {
        return;
      }

      StorageLibraryChange *wrapper = StorageLibraryChange::Unwrap<StorageLibraryChange>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Path;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousPathGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChange^>(info.This())) {
        return;
      }

      StorageLibraryChange *wrapper = StorageLibraryChange::Unwrap<StorageLibraryChange>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->PreviousPath;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::StorageLibraryChange^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorageLibraryChange(::Windows::Storage::StorageLibraryChange^ wintRtInstance);
      friend ::Windows::Storage::StorageLibraryChange^ UnwrapStorageLibraryChange(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorageLibraryChange::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorageLibraryChange(::Windows::Storage::StorageLibraryChange^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorageLibraryChange::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::StorageLibraryChange^ UnwrapStorageLibraryChange(Local<Value> value) {
     return StorageLibraryChange::Unwrap<StorageLibraryChange>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorageLibraryChange(Local<Object> exports) {
    StorageLibraryChange::Init(exports);
  }

  class StorageLibraryChangeReader : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorageLibraryChangeReader").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "readBatchAsync", ReadBatchAsync);
            Nan::SetPrototypeMethod(localRef, "acceptChangesAsync", AcceptChangesAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorageLibraryChangeReader").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorageLibraryChangeReader(::Windows::Storage::StorageLibraryChangeReader^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::StorageLibraryChangeReader^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChangeReader^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::StorageLibraryChangeReader^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorageLibraryChangeReader *wrapperInstance = new StorageLibraryChangeReader(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChangeReader^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::StorageLibraryChangeReader^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::StorageLibraryChangeReader^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorageLibraryChangeReader(winRtInstance));
    }

    static void ReadBatchAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChangeReader^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageLibraryChangeReader *wrapper = StorageLibraryChangeReader::Unwrap<StorageLibraryChangeReader>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::StorageLibraryChange^>^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->ReadBatchAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::StorageLibraryChange^>^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Storage::StorageLibraryChange^>::CreateVectorViewWrapper(result, 
            [](::Windows::Storage::StorageLibraryChange^ val) -> Local<Value> {
              return WrapStorageLibraryChange(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChange^>(value);
            },
            [](Local<Value> value) -> ::Windows::Storage::StorageLibraryChange^ {
              return UnwrapStorageLibraryChange(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void AcceptChangesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageLibraryChangeReader^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageLibraryChangeReader *wrapper = StorageLibraryChangeReader::Unwrap<StorageLibraryChangeReader>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->AcceptChangesAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }






    private:
      ::Windows::Storage::StorageLibraryChangeReader^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorageLibraryChangeReader(::Windows::Storage::StorageLibraryChangeReader^ wintRtInstance);
      friend ::Windows::Storage::StorageLibraryChangeReader^ UnwrapStorageLibraryChangeReader(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorageLibraryChangeReader::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorageLibraryChangeReader(::Windows::Storage::StorageLibraryChangeReader^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorageLibraryChangeReader::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::StorageLibraryChangeReader^ UnwrapStorageLibraryChangeReader(Local<Value> value) {
     return StorageLibraryChangeReader::Unwrap<StorageLibraryChangeReader>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorageLibraryChangeReader(Local<Object> exports) {
    StorageLibraryChangeReader::Init(exports);
  }

  class IStreamedFileDataRequest : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStreamedFileDataRequest").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "failAndClose", FailAndClose);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStreamedFileDataRequest").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStreamedFileDataRequest(::Windows::Storage::IStreamedFileDataRequest^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStreamedFileDataRequest^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStreamedFileDataRequest^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStreamedFileDataRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStreamedFileDataRequest *wrapperInstance = new IStreamedFileDataRequest(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStreamedFileDataRequest^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStreamedFileDataRequest^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStreamedFileDataRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStreamedFileDataRequest(winRtInstance));
    }


    static void FailAndClose(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStreamedFileDataRequest^>(info.This())) {
        return;
      }

      IStreamedFileDataRequest *wrapper = IStreamedFileDataRequest::Unwrap<IStreamedFileDataRequest>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StreamedFileFailureMode arg0 = static_cast<::Windows::Storage::StreamedFileFailureMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->FailAndClose(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Storage::IStreamedFileDataRequest^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStreamedFileDataRequest(::Windows::Storage::IStreamedFileDataRequest^ wintRtInstance);
      friend ::Windows::Storage::IStreamedFileDataRequest^ UnwrapIStreamedFileDataRequest(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStreamedFileDataRequest::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStreamedFileDataRequest(::Windows::Storage::IStreamedFileDataRequest^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStreamedFileDataRequest::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStreamedFileDataRequest^ UnwrapIStreamedFileDataRequest(Local<Value> value) {
     return IStreamedFileDataRequest::Unwrap<IStreamedFileDataRequest>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStreamedFileDataRequest(Local<Object> exports) {
    IStreamedFileDataRequest::Init(exports);
  }

  class StreamedFileDataRequest : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StreamedFileDataRequest").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "close", Close);
            Nan::SetPrototypeMethod(localRef, "failAndClose", FailAndClose);
          

          
            Nan::SetPrototypeMethod(localRef, "writeAsync", WriteAsync);
            Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StreamedFileDataRequest").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StreamedFileDataRequest(::Windows::Storage::StreamedFileDataRequest^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::StreamedFileDataRequest^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StreamedFileDataRequest^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::StreamedFileDataRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StreamedFileDataRequest *wrapperInstance = new StreamedFileDataRequest(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StreamedFileDataRequest^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::StreamedFileDataRequest^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::StreamedFileDataRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStreamedFileDataRequest(winRtInstance));
    }

    static void WriteAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StreamedFileDataRequest^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StreamedFileDataRequest *wrapper = StreamedFileDataRequest::Unwrap<StreamedFileDataRequest>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned int, unsigned int>^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->WriteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<unsigned int> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StreamedFileDataRequest^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StreamedFileDataRequest *wrapper = StreamedFileDataRequest::Unwrap<StreamedFileDataRequest>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StreamedFileDataRequest^>(info.This())) {
        return;
      }

      StreamedFileDataRequest *wrapper = StreamedFileDataRequest::Unwrap<StreamedFileDataRequest>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void FailAndClose(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StreamedFileDataRequest^>(info.This())) {
        return;
      }

      StreamedFileDataRequest *wrapper = StreamedFileDataRequest::Unwrap<StreamedFileDataRequest>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StreamedFileFailureMode arg0 = static_cast<::Windows::Storage::StreamedFileFailureMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->FailAndClose(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Storage::StreamedFileDataRequest^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStreamedFileDataRequest(::Windows::Storage::StreamedFileDataRequest^ wintRtInstance);
      friend ::Windows::Storage::StreamedFileDataRequest^ UnwrapStreamedFileDataRequest(Local<Value> value);
  };

  Persistent<FunctionTemplate> StreamedFileDataRequest::s_constructorTemplate;

  v8::Local<v8::Value> WrapStreamedFileDataRequest(::Windows::Storage::StreamedFileDataRequest^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StreamedFileDataRequest::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::StreamedFileDataRequest^ UnwrapStreamedFileDataRequest(Local<Value> value) {
     return StreamedFileDataRequest::Unwrap<StreamedFileDataRequest>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStreamedFileDataRequest(Local<Object> exports) {
    StreamedFileDataRequest::Init(exports);
  }

  class StorageStreamTransaction : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorageStreamTransaction").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "close", Close);
          

          
            Nan::SetPrototypeMethod(localRef, "commitAsync", CommitAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("stream").ToLocalChecked(), StreamGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorageStreamTransaction").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorageStreamTransaction(::Windows::Storage::StorageStreamTransaction^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::StorageStreamTransaction^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageStreamTransaction^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::StorageStreamTransaction^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorageStreamTransaction *wrapperInstance = new StorageStreamTransaction(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageStreamTransaction^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::StorageStreamTransaction^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::StorageStreamTransaction^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorageStreamTransaction(winRtInstance));
    }

    static void CommitAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageStreamTransaction^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageStreamTransaction *wrapper = StorageStreamTransaction::Unwrap<StorageStreamTransaction>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->CommitAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageStreamTransaction^>(info.This())) {
        return;
      }

      StorageStreamTransaction *wrapper = StorageStreamTransaction::Unwrap<StorageStreamTransaction>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void StreamGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageStreamTransaction^>(info.This())) {
        return;
      }

      StorageStreamTransaction *wrapper = StorageStreamTransaction::Unwrap<StorageStreamTransaction>(info.This());

      try  {
        ::Windows::Storage::Streams::IRandomAccessStream^ result = wrapper->_instance->Stream;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IRandomAccessStream", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::StorageStreamTransaction^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorageStreamTransaction(::Windows::Storage::StorageStreamTransaction^ wintRtInstance);
      friend ::Windows::Storage::StorageStreamTransaction^ UnwrapStorageStreamTransaction(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorageStreamTransaction::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorageStreamTransaction(::Windows::Storage::StorageStreamTransaction^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorageStreamTransaction::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::StorageStreamTransaction^ UnwrapStorageStreamTransaction(Local<Value> value) {
     return StorageStreamTransaction::Unwrap<StorageStreamTransaction>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorageStreamTransaction(Local<Object> exports) {
    StorageStreamTransaction::Init(exports);
  }

  class IStorageFolder : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStorageFolder").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "createFileAsync", CreateFileAsync);
            Nan::SetPrototypeMethod(localRef, "createFolderAsync", CreateFolderAsync);
            Nan::SetPrototypeMethod(localRef, "getFileAsync", GetFileAsync);
            Nan::SetPrototypeMethod(localRef, "getFolderAsync", GetFolderAsync);
            Nan::SetPrototypeMethod(localRef, "getItemAsync", GetItemAsync);
            Nan::SetPrototypeMethod(localRef, "getFilesAsync", GetFilesAsync);
            Nan::SetPrototypeMethod(localRef, "getFoldersAsync", GetFoldersAsync);
            Nan::SetPrototypeMethod(localRef, "getItemsAsync", GetItemsAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStorageFolder").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStorageFolder(::Windows::Storage::IStorageFolder^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStorageFolder^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStorageFolder^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStorageFolder *wrapperInstance = new IStorageFolder(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStorageFolder^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStorageFolder^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStorageFolder(winRtInstance));
    }

    static void CreateFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFolder *wrapper = IStorageFolder::Unwrap<IStorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->CreateFileAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::CreationCollisionOption arg1 = static_cast<::Windows::Storage::CreationCollisionOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->CreateFileAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void CreateFolderAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFolder *wrapper = IStorageFolder::Unwrap<IStorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->CreateFolderAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::CreationCollisionOption arg1 = static_cast<::Windows::Storage::CreationCollisionOption>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->CreateFolderAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFolder *wrapper = IStorageFolder::Unwrap<IStorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->GetFileAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetFolderAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFolder *wrapper = IStorageFolder::Unwrap<IStorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->GetFolderAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetItemAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFolder *wrapper = IStorageFolder::Unwrap<IStorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::IStorageItem^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->GetItemAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::IStorageItem^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIStorageItem(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetFilesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFolder *wrapper = IStorageFolder::Unwrap<IStorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::StorageFile^>^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetFilesAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::StorageFile^>^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Storage::StorageFile^>::CreateVectorViewWrapper(result, 
            [](::Windows::Storage::StorageFile^ val) -> Local<Value> {
              return WrapStorageFile(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFile^>(value);
            },
            [](Local<Value> value) -> ::Windows::Storage::StorageFile^ {
              return UnwrapStorageFile(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetFoldersAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFolder *wrapper = IStorageFolder::Unwrap<IStorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::StorageFolder^>^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetFoldersAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::StorageFolder^>^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Storage::StorageFolder^>::CreateVectorViewWrapper(result, 
            [](::Windows::Storage::StorageFolder^ val) -> Local<Value> {
              return WrapStorageFolder(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageFolder^>(value);
            },
            [](Local<Value> value) -> ::Windows::Storage::StorageFolder^ {
              return UnwrapStorageFolder(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void GetItemsAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFolder *wrapper = IStorageFolder::Unwrap<IStorageFolder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::IStorageItem^>^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetItemsAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVectorView<::Windows::Storage::IStorageItem^>^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorViewWrapper<::Windows::Storage::IStorageItem^>::CreateVectorViewWrapper(result, 
            [](::Windows::Storage::IStorageItem^ val) -> Local<Value> {
              return WrapIStorageItem(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(value);
            },
            [](Local<Value> value) -> ::Windows::Storage::IStorageItem^ {
              return UnwrapIStorageItem(value);
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }






    private:
      ::Windows::Storage::IStorageFolder^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStorageFolder(::Windows::Storage::IStorageFolder^ wintRtInstance);
      friend ::Windows::Storage::IStorageFolder^ UnwrapIStorageFolder(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStorageFolder::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStorageFolder(::Windows::Storage::IStorageFolder^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStorageFolder::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStorageFolder^ UnwrapIStorageFolder(Local<Value> value) {
     return IStorageFolder::Unwrap<IStorageFolder>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStorageFolder(Local<Object> exports) {
    IStorageFolder::Init(exports);
  }

  class IStorageFile : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStorageFile").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "openAsync", OpenAsync);
            Nan::SetPrototypeMethod(localRef, "openTransactedWriteAsync", OpenTransactedWriteAsync);
            Nan::SetPrototypeMethod(localRef, "copyAsync", CopyAsync);
            Nan::SetPrototypeMethod(localRef, "copyAndReplaceAsync", CopyAndReplaceAsync);
            Nan::SetPrototypeMethod(localRef, "moveAsync", MoveAsync);
            Nan::SetPrototypeMethod(localRef, "moveAndReplaceAsync", MoveAndReplaceAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("contentType").ToLocalChecked(), ContentTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("fileType").ToLocalChecked(), FileTypeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStorageFile").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStorageFile(::Windows::Storage::IStorageFile^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStorageFile^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStorageFile^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStorageFile *wrapperInstance = new IStorageFile(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStorageFile^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStorageFile^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStorageFile(winRtInstance));
    }

    static void OpenAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFile *wrapper = IStorageFile::Unwrap<IStorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IRandomAccessStream^>^ op;


      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileAccessMode arg0 = static_cast<::Windows::Storage::FileAccessMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->OpenAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IRandomAccessStream^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IRandomAccessStream", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void OpenTransactedWriteAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFile *wrapper = IStorageFile::Unwrap<IStorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageStreamTransaction^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->OpenTransactedWriteAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageStreamTransaction^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageStreamTransaction(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void CopyAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFile *wrapper = IStorageFile::Unwrap<IStorageFile>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFile^>^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          
          op = wrapper->_instance->CopyAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          op = wrapper->_instance->CopyAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0])
        && info[1]->IsString()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Storage::NameCollisionOption arg2 = static_cast<::Windows::Storage::NameCollisionOption>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->CopyAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFile^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFile(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void CopyAndReplaceAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFile *wrapper = IStorageFile::Unwrap<IStorageFile>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          
          op = wrapper->_instance->CopyAndReplaceAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void MoveAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFile *wrapper = IStorageFile::Unwrap<IStorageFile>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          
          op = wrapper->_instance->MoveAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0])
        && info[1]->IsString())
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          op = wrapper->_instance->MoveAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder^>(info[0])
        && info[1]->IsString()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::IStorageFolder^ arg0 = UnwrapIStorageFolder(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Storage::NameCollisionOption arg2 = static_cast<::Windows::Storage::NameCollisionOption>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->MoveAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void MoveAndReplaceAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFile *wrapper = IStorageFile::Unwrap<IStorageFile>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          
          op = wrapper->_instance->MoveAndReplaceAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    static void ContentTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info.This())) {
        return;
      }

      IStorageFile *wrapper = IStorageFile::Unwrap<IStorageFile>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ContentType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FileTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info.This())) {
        return;
      }

      IStorageFile *wrapper = IStorageFile::Unwrap<IStorageFile>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FileType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::IStorageFile^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStorageFile(::Windows::Storage::IStorageFile^ wintRtInstance);
      friend ::Windows::Storage::IStorageFile^ UnwrapIStorageFile(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStorageFile::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStorageFile(::Windows::Storage::IStorageFile^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStorageFile::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStorageFile^ UnwrapIStorageFile(Local<Value> value) {
     return IStorageFile::Unwrap<IStorageFile>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStorageFile(Local<Object> exports) {
    IStorageFile::Init(exports);
  }

  class IStorageItem2 : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStorageItem2").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "isEqual", IsEqual);
          

          
            Nan::SetPrototypeMethod(localRef, "getParentAsync", GetParentAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStorageItem2").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStorageItem2(::Windows::Storage::IStorageItem2^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStorageItem2^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem2^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStorageItem2^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStorageItem2 *wrapperInstance = new IStorageItem2(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem2^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStorageItem2^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStorageItem2^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStorageItem2(winRtInstance));
    }

    static void GetParentAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem2^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageItem2 *wrapper = IStorageItem2::Unwrap<IStorageItem2>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageFolder^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetParentAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageFolder^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageFolder(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void IsEqual(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem2^>(info.This())) {
        return;
      }

      IStorageItem2 *wrapper = IStorageItem2::Unwrap<IStorageItem2>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItem^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageItem^ arg0 = UnwrapIStorageItem(info[0]);
          
          bool result;
          result = wrapper->_instance->IsEqual(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Storage::IStorageItem2^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStorageItem2(::Windows::Storage::IStorageItem2^ wintRtInstance);
      friend ::Windows::Storage::IStorageItem2^ UnwrapIStorageItem2(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStorageItem2::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStorageItem2(::Windows::Storage::IStorageItem2^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStorageItem2::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStorageItem2^ UnwrapIStorageItem2(Local<Value> value) {
     return IStorageItem2::Unwrap<IStorageItem2>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStorageItem2(Local<Object> exports) {
    IStorageItem2::Init(exports);
  }

  class IStorageItemProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStorageItemProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getThumbnailAsync", GetThumbnailAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayType").ToLocalChecked(), DisplayTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("folderRelativeId").ToLocalChecked(), FolderRelativeIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("properties").ToLocalChecked(), PropertiesGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStorageItemProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStorageItemProperties(::Windows::Storage::IStorageItemProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStorageItemProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStorageItemProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStorageItemProperties *wrapperInstance = new IStorageItemProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStorageItemProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStorageItemProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStorageItemProperties(winRtInstance));
    }

    static void GetThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemProperties^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageItemProperties *wrapper = IStorageItemProperties::Unwrap<IStorageItemProperties>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::FileProperties::StorageItemThumbnail^>^ op;


      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetThumbnailAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsUint32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetThumbnailAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::FileProperties::ThumbnailOptions arg2 = static_cast<::Windows::Storage::FileProperties::ThumbnailOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->GetThumbnailAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::FileProperties::StorageItemThumbnail^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "StorageItemThumbnail", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemProperties^>(info.This())) {
        return;
      }

      IStorageItemProperties *wrapper = IStorageItemProperties::Unwrap<IStorageItemProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DisplayTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemProperties^>(info.This())) {
        return;
      }

      IStorageItemProperties *wrapper = IStorageItemProperties::Unwrap<IStorageItemProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FolderRelativeIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemProperties^>(info.This())) {
        return;
      }

      IStorageItemProperties *wrapper = IStorageItemProperties::Unwrap<IStorageItemProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FolderRelativeId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemProperties^>(info.This())) {
        return;
      }

      IStorageItemProperties *wrapper = IStorageItemProperties::Unwrap<IStorageItemProperties>(info.This());

      try  {
        ::Windows::Storage::FileProperties::StorageItemContentProperties^ result = wrapper->_instance->Properties;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "StorageItemContentProperties", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::IStorageItemProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStorageItemProperties(::Windows::Storage::IStorageItemProperties^ wintRtInstance);
      friend ::Windows::Storage::IStorageItemProperties^ UnwrapIStorageItemProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStorageItemProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStorageItemProperties(::Windows::Storage::IStorageItemProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStorageItemProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStorageItemProperties^ UnwrapIStorageItemProperties(Local<Value> value) {
     return IStorageItemProperties::Unwrap<IStorageItemProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStorageItemProperties(Local<Object> exports) {
    IStorageItemProperties::Init(exports);
  }

  class IStorageItemProperties2 : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStorageItemProperties2").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getScaledImageAsThumbnailAsync", GetScaledImageAsThumbnailAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStorageItemProperties2").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStorageItemProperties2(::Windows::Storage::IStorageItemProperties2^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStorageItemProperties2^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemProperties2^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStorageItemProperties2^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStorageItemProperties2 *wrapperInstance = new IStorageItemProperties2(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemProperties2^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStorageItemProperties2^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStorageItemProperties2^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStorageItemProperties2(winRtInstance));
    }

    static void GetScaledImageAsThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemProperties2^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageItemProperties2 *wrapper = IStorageItemProperties2::Unwrap<IStorageItemProperties2>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::FileProperties::StorageItemThumbnail^>^ op;


      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetScaledImageAsThumbnailAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsUint32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetScaledImageAsThumbnailAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileProperties::ThumbnailMode arg0 = static_cast<::Windows::Storage::FileProperties::ThumbnailMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::FileProperties::ThumbnailOptions arg2 = static_cast<::Windows::Storage::FileProperties::ThumbnailOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->GetScaledImageAsThumbnailAsync(arg0,arg1,arg2);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::FileProperties::StorageItemThumbnail^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.FileProperties", "StorageItemThumbnail", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }






    private:
      ::Windows::Storage::IStorageItemProperties2^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStorageItemProperties2(::Windows::Storage::IStorageItemProperties2^ wintRtInstance);
      friend ::Windows::Storage::IStorageItemProperties2^ UnwrapIStorageItemProperties2(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStorageItemProperties2::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStorageItemProperties2(::Windows::Storage::IStorageItemProperties2^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStorageItemProperties2::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStorageItemProperties2^ UnwrapIStorageItemProperties2(Local<Value> value) {
     return IStorageItemProperties2::Unwrap<IStorageItemProperties2>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStorageItemProperties2(Local<Object> exports) {
    IStorageItemProperties2::Init(exports);
  }

  class IStorageItemPropertiesWithProvider : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStorageItemPropertiesWithProvider").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("provider").ToLocalChecked(), ProviderGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStorageItemPropertiesWithProvider").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStorageItemPropertiesWithProvider(::Windows::Storage::IStorageItemPropertiesWithProvider^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStorageItemPropertiesWithProvider^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemPropertiesWithProvider^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStorageItemPropertiesWithProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStorageItemPropertiesWithProvider *wrapperInstance = new IStorageItemPropertiesWithProvider(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemPropertiesWithProvider^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStorageItemPropertiesWithProvider^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStorageItemPropertiesWithProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStorageItemPropertiesWithProvider(winRtInstance));
    }





    static void ProviderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageItemPropertiesWithProvider^>(info.This())) {
        return;
      }

      IStorageItemPropertiesWithProvider *wrapper = IStorageItemPropertiesWithProvider::Unwrap<IStorageItemPropertiesWithProvider>(info.This());

      try  {
        ::Windows::Storage::StorageProvider^ result = wrapper->_instance->Provider;
        info.GetReturnValue().Set(WrapStorageProvider(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::IStorageItemPropertiesWithProvider^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStorageItemPropertiesWithProvider(::Windows::Storage::IStorageItemPropertiesWithProvider^ wintRtInstance);
      friend ::Windows::Storage::IStorageItemPropertiesWithProvider^ UnwrapIStorageItemPropertiesWithProvider(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStorageItemPropertiesWithProvider::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStorageItemPropertiesWithProvider(::Windows::Storage::IStorageItemPropertiesWithProvider^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStorageItemPropertiesWithProvider::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStorageItemPropertiesWithProvider^ UnwrapIStorageItemPropertiesWithProvider(Local<Value> value) {
     return IStorageItemPropertiesWithProvider::Unwrap<IStorageItemPropertiesWithProvider>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStorageItemPropertiesWithProvider(Local<Object> exports) {
    IStorageItemPropertiesWithProvider::Init(exports);
  }

  class StorageProvider : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("StorageProvider").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "isPropertySupportedForPartialFileAsync", IsPropertySupportedForPartialFileAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("StorageProvider").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      StorageProvider(::Windows::Storage::StorageProvider^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::StorageProvider^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageProvider^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::StorageProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      StorageProvider *wrapperInstance = new StorageProvider(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageProvider^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::StorageProvider^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::StorageProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapStorageProvider(winRtInstance));
    }

    static void IsPropertySupportedForPartialFileAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageProvider^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      StorageProvider *wrapper = StorageProvider::Unwrap<StorageProvider>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->IsPropertySupportedForPartialFileAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<bool> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageProvider^>(info.This())) {
        return;
      }

      StorageProvider *wrapper = StorageProvider::Unwrap<StorageProvider>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::StorageProvider^>(info.This())) {
        return;
      }

      StorageProvider *wrapper = StorageProvider::Unwrap<StorageProvider>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Id;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::StorageProvider^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapStorageProvider(::Windows::Storage::StorageProvider^ wintRtInstance);
      friend ::Windows::Storage::StorageProvider^ UnwrapStorageProvider(Local<Value> value);
  };

  Persistent<FunctionTemplate> StorageProvider::s_constructorTemplate;

  v8::Local<v8::Value> WrapStorageProvider(::Windows::Storage::StorageProvider^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(StorageProvider::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::StorageProvider^ UnwrapStorageProvider(Local<Value> value) {
     return StorageProvider::Unwrap<StorageProvider>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitStorageProvider(Local<Object> exports) {
    StorageProvider::Init(exports);
  }

  class IStorageFilePropertiesWithAvailability : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStorageFilePropertiesWithAvailability").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isAvailable").ToLocalChecked(), IsAvailableGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStorageFilePropertiesWithAvailability").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStorageFilePropertiesWithAvailability(::Windows::Storage::IStorageFilePropertiesWithAvailability^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStorageFilePropertiesWithAvailability^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFilePropertiesWithAvailability^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStorageFilePropertiesWithAvailability^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStorageFilePropertiesWithAvailability *wrapperInstance = new IStorageFilePropertiesWithAvailability(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFilePropertiesWithAvailability^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStorageFilePropertiesWithAvailability^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStorageFilePropertiesWithAvailability^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStorageFilePropertiesWithAvailability(winRtInstance));
    }





    static void IsAvailableGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFilePropertiesWithAvailability^>(info.This())) {
        return;
      }

      IStorageFilePropertiesWithAvailability *wrapper = IStorageFilePropertiesWithAvailability::Unwrap<IStorageFilePropertiesWithAvailability>(info.This());

      try  {
        bool result = wrapper->_instance->IsAvailable;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::IStorageFilePropertiesWithAvailability^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStorageFilePropertiesWithAvailability(::Windows::Storage::IStorageFilePropertiesWithAvailability^ wintRtInstance);
      friend ::Windows::Storage::IStorageFilePropertiesWithAvailability^ UnwrapIStorageFilePropertiesWithAvailability(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStorageFilePropertiesWithAvailability::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStorageFilePropertiesWithAvailability(::Windows::Storage::IStorageFilePropertiesWithAvailability^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStorageFilePropertiesWithAvailability::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStorageFilePropertiesWithAvailability^ UnwrapIStorageFilePropertiesWithAvailability(Local<Value> value) {
     return IStorageFilePropertiesWithAvailability::Unwrap<IStorageFilePropertiesWithAvailability>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStorageFilePropertiesWithAvailability(Local<Object> exports) {
    IStorageFilePropertiesWithAvailability::Init(exports);
  }

  class IStorageFolder2 : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStorageFolder2").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "tryGetItemAsync", TryGetItemAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStorageFolder2").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStorageFolder2(::Windows::Storage::IStorageFolder2^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStorageFolder2^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder2^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStorageFolder2^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStorageFolder2 *wrapperInstance = new IStorageFolder2(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder2^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStorageFolder2^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStorageFolder2^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStorageFolder2(winRtInstance));
    }

    static void TryGetItemAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFolder2^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFolder2 *wrapper = IStorageFolder2::Unwrap<IStorageFolder2>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::IStorageItem^>^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->TryGetItemAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::IStorageItem^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapIStorageItem(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }






    private:
      ::Windows::Storage::IStorageFolder2^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStorageFolder2(::Windows::Storage::IStorageFolder2^ wintRtInstance);
      friend ::Windows::Storage::IStorageFolder2^ UnwrapIStorageFolder2(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStorageFolder2::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStorageFolder2(::Windows::Storage::IStorageFolder2^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStorageFolder2::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStorageFolder2^ UnwrapIStorageFolder2(Local<Value> value) {
     return IStorageFolder2::Unwrap<IStorageFolder2>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStorageFolder2(Local<Object> exports) {
    IStorageFolder2::Init(exports);
  }

  class IStorageFile2 : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IStorageFile2").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "openAsync", OpenAsync);
            Nan::SetPrototypeMethod(localRef, "openTransactedWriteAsync", OpenTransactedWriteAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IStorageFile2").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IStorageFile2(::Windows::Storage::IStorageFile2^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::IStorageFile2^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile2^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::IStorageFile2^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IStorageFile2 *wrapperInstance = new IStorageFile2(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile2^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::IStorageFile2^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::IStorageFile2^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIStorageFile2(winRtInstance));
    }

    static void OpenAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile2^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFile2 *wrapper = IStorageFile2::Unwrap<IStorageFile2>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IRandomAccessStream^>^ op;


      if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Storage::FileAccessMode arg0 = static_cast<::Windows::Storage::FileAccessMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Storage::StorageOpenOptions arg1 = static_cast<::Windows::Storage::StorageOpenOptions>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->OpenAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IRandomAccessStream^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IRandomAccessStream", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void OpenTransactedWriteAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile2^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IStorageFile2 *wrapper = IStorageFile2::Unwrap<IStorageFile2>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::StorageStreamTransaction^>^ op;


      if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::StorageOpenOptions arg0 = static_cast<::Windows::Storage::StorageOpenOptions>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->OpenTransactedWriteAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::StorageStreamTransaction^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapStorageStreamTransaction(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }






    private:
      ::Windows::Storage::IStorageFile2^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIStorageFile2(::Windows::Storage::IStorageFile2^ wintRtInstance);
      friend ::Windows::Storage::IStorageFile2^ UnwrapIStorageFile2(Local<Value> value);
  };

  Persistent<FunctionTemplate> IStorageFile2::s_constructorTemplate;

  v8::Local<v8::Value> WrapIStorageFile2(::Windows::Storage::IStorageFile2^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IStorageFile2::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::IStorageFile2^ UnwrapIStorageFile2(Local<Value> value) {
     return IStorageFile2::Unwrap<IStorageFile2>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIStorageFile2(Local<Object> exports) {
    IStorageFile2::Init(exports);
  }

  class FileIO : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("FileIO").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;





        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        func = Nan::GetFunction(Nan::New<FunctionTemplate>(ReadTextAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("readTextAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(WriteTextAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("writeTextAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(AppendTextAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("appendTextAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(ReadLinesAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("readLinesAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(WriteLinesAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("writeLinesAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(AppendLinesAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("appendLinesAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(ReadBufferAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("readBufferAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(WriteBufferAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("writeBufferAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(WriteBytesAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("writeBytesAsync").ToLocalChecked(), func);


        Nan::Set(exports, Nan::New<String>("FileIO").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      FileIO(::Windows::Storage::FileIO^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::FileIO^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::FileIO^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::FileIO^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      FileIO *wrapperInstance = new FileIO(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::FileIO^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::FileIO^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::FileIO^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapFileIO(winRtInstance));
    }




    static void ReadTextAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Platform::String^>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
            
          op = ::Windows::Storage::FileIO::ReadTextAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          ::Windows::Storage::Streams::UnicodeEncoding arg1 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[1]).FromMaybe(0));
            
          op = ::Windows::Storage::FileIO::ReadTextAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Platform::String^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::NewString(result->Data());
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void WriteTextAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && info[1]->IsString())
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
            
          op = ::Windows::Storage::FileIO::WriteTextAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && info[1]->IsString()
          && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Storage::Streams::UnicodeEncoding arg2 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[2]).FromMaybe(0));
            
          op = ::Windows::Storage::FileIO::WriteTextAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void AppendTextAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && info[1]->IsString())
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
            
          op = ::Windows::Storage::FileIO::AppendTextAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && info[1]->IsString()
          && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Storage::Streams::UnicodeEncoding arg2 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[2]).FromMaybe(0));
            
          op = ::Windows::Storage::FileIO::AppendTextAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void ReadLinesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVector<::Platform::String^>^>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
            
          op = ::Windows::Storage::FileIO::ReadLinesAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          ::Windows::Storage::Streams::UnicodeEncoding arg1 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[1]).FromMaybe(0));
            
          op = ::Windows::Storage::FileIO::ReadLinesAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVector<::Platform::String^>^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorWrapper<::Platform::String^>::CreateVectorWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void WriteLinesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray()))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
            
          op = ::Windows::Storage::FileIO::WriteLinesAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray())
          && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          ::Windows::Storage::Streams::UnicodeEncoding arg2 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[2]).FromMaybe(0));
            
          op = ::Windows::Storage::FileIO::WriteLinesAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void AppendLinesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray()))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
            
          op = ::Windows::Storage::FileIO::AppendLinesAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray())
          && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          ::Windows::Storage::Streams::UnicodeEncoding arg2 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[2]).FromMaybe(0));
            
          op = ::Windows::Storage::FileIO::AppendLinesAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void ReadBufferAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IBuffer^>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
            
          op = ::Windows::Storage::FileIO::ReadBufferAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IBuffer^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void WriteBufferAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[1]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          ::Windows::Storage::Streams::IBuffer^ arg1 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[1]));
            
          op = ::Windows::Storage::FileIO::WriteBufferAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void WriteBytesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0])
          && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<unsigned char>^>(info[1]) || info[1]->IsArray()))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          ::Platform::Array<unsigned char>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<unsigned char>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<unsigned char>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsInt32();
                 },
                 [](Local<Value> value) -> unsigned char {
                   return static_cast<unsigned char>(Nan::To<int32_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<unsigned char>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
            
          op = ::Windows::Storage::FileIO::WriteBytesAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    private:
      ::Windows::Storage::FileIO^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapFileIO(::Windows::Storage::FileIO^ wintRtInstance);
      friend ::Windows::Storage::FileIO^ UnwrapFileIO(Local<Value> value);
  };

  Persistent<FunctionTemplate> FileIO::s_constructorTemplate;

  v8::Local<v8::Value> WrapFileIO(::Windows::Storage::FileIO^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(FileIO::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::FileIO^ UnwrapFileIO(Local<Value> value) {
     return FileIO::Unwrap<FileIO>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitFileIO(Local<Object> exports) {
    FileIO::Init(exports);
  }

  class PathIO : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("PathIO").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;





        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        func = Nan::GetFunction(Nan::New<FunctionTemplate>(ReadTextAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("readTextAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(WriteTextAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("writeTextAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(AppendTextAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("appendTextAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(ReadLinesAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("readLinesAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(WriteLinesAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("writeLinesAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(AppendLinesAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("appendLinesAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(ReadBufferAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("readBufferAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(WriteBufferAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("writeBufferAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(WriteBytesAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("writeBytesAsync").ToLocalChecked(), func);


        Nan::Set(exports, Nan::New<String>("PathIO").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      PathIO(::Windows::Storage::PathIO^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::PathIO^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::PathIO^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::PathIO^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PathIO *wrapperInstance = new PathIO(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::PathIO^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::PathIO^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::PathIO^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapPathIO(winRtInstance));
    }




    static void ReadTextAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Platform::String^>^ op;


      if (info.Length() == 2
          && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
            
          op = ::Windows::Storage::PathIO::ReadTextAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 3
          && info[0]->IsString()
          && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::Streams::UnicodeEncoding arg1 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[1]).FromMaybe(0));
            
          op = ::Windows::Storage::PathIO::ReadTextAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Platform::String^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::NewString(result->Data());
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void WriteTextAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && info[0]->IsString()
          && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
            
          op = ::Windows::Storage::PathIO::WriteTextAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && info[0]->IsString()
          && info[1]->IsString()
          && info[2]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Storage::Streams::UnicodeEncoding arg2 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[2]).FromMaybe(0));
            
          op = ::Windows::Storage::PathIO::WriteTextAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void AppendTextAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && info[0]->IsString()
          && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
            
          op = ::Windows::Storage::PathIO::AppendTextAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && info[0]->IsString()
          && info[1]->IsString()
          && info[2]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          ::Windows::Storage::Streams::UnicodeEncoding arg2 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[2]).FromMaybe(0));
            
          op = ::Windows::Storage::PathIO::AppendTextAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void ReadLinesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Foundation::Collections::IVector<::Platform::String^>^>^ op;


      if (info.Length() == 2
          && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
            
          op = ::Windows::Storage::PathIO::ReadLinesAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 3
          && info[0]->IsString()
          && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::Streams::UnicodeEncoding arg1 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[1]).FromMaybe(0));
            
          op = ::Windows::Storage::PathIO::ReadLinesAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Foundation::Collections::IVector<::Platform::String^>^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Collections::VectorWrapper<::Platform::String^>::CreateVectorWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          );
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void WriteLinesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && info[0]->IsString()
          && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray()))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
            
          op = ::Windows::Storage::PathIO::WriteLinesAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && info[0]->IsString()
          && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray())
          && info[2]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          ::Windows::Storage::Streams::UnicodeEncoding arg2 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[2]).FromMaybe(0));
            
          op = ::Windows::Storage::PathIO::WriteLinesAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void AppendLinesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && info[0]->IsString()
          && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray()))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
            
          op = ::Windows::Storage::PathIO::AppendLinesAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && info[0]->IsString()
          && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[1]) || info[1]->IsArray())
          && info[2]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
          ::Windows::Storage::Streams::UnicodeEncoding arg2 = static_cast<::Windows::Storage::Streams::UnicodeEncoding>(Nan::To<int32_t>(info[2]).FromMaybe(0));
            
          op = ::Windows::Storage::PathIO::AppendLinesAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void ReadBufferAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Streams::IBuffer^>^ op;


      if (info.Length() == 2
          && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
            
          op = ::Windows::Storage::PathIO::ReadBufferAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IBuffer^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void WriteBufferAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && info[0]->IsString()
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::Streams::IBuffer^ arg1 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[1]));
            
          op = ::Windows::Storage::PathIO::WriteBufferAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void WriteBytesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
          && info[0]->IsString()
          && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<unsigned char>^>(info[1]) || info[1]->IsArray()))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Array<unsigned char>^ arg1 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<unsigned char>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<unsigned char>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsInt32();
                 },
                 [](Local<Value> value) -> unsigned char {
                   return static_cast<unsigned char>(Nan::To<int32_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<unsigned char>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[1]);
            
          op = ::Windows::Storage::PathIO::WriteBytesAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t)
      {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


                Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    private:
      ::Windows::Storage::PathIO^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapPathIO(::Windows::Storage::PathIO^ wintRtInstance);
      friend ::Windows::Storage::PathIO^ UnwrapPathIO(Local<Value> value);
  };

  Persistent<FunctionTemplate> PathIO::s_constructorTemplate;

  v8::Local<v8::Value> WrapPathIO(::Windows::Storage::PathIO^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PathIO::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::PathIO^ UnwrapPathIO(Local<Value> value) {
     return PathIO::Unwrap<PathIO>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPathIO(Local<Object> exports) {
    PathIO::Init(exports);
  }

  class CachedFileManager : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("CachedFileManager").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;





        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "deferUpdates", DeferUpdates);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CompleteUpdatesAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("completeUpdatesAsync").ToLocalChecked(), func);


        Nan::Set(exports, Nan::New<String>("CachedFileManager").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      CachedFileManager(::Windows::Storage::CachedFileManager^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::CachedFileManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::CachedFileManager^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::CachedFileManager^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      CachedFileManager *wrapperInstance = new CachedFileManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::CachedFileManager^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::CachedFileManager^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::CachedFileManager^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapCachedFileManager(winRtInstance));
    }




    static void CompleteUpdatesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::Provider::FileUpdateStatus>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
            
          op = ::Windows::Storage::CachedFileManager::CompleteUpdatesAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::Provider::FileUpdateStatus> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(static_cast<int>(result));
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void DeferUpdates(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = UnwrapIStorageFile(info[0]);
          
          ::Windows::Storage::CachedFileManager::DeferUpdates(arg0);
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    private:
      ::Windows::Storage::CachedFileManager^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapCachedFileManager(::Windows::Storage::CachedFileManager^ wintRtInstance);
      friend ::Windows::Storage::CachedFileManager^ UnwrapCachedFileManager(Local<Value> value);
  };

  Persistent<FunctionTemplate> CachedFileManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapCachedFileManager(::Windows::Storage::CachedFileManager^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(CachedFileManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::CachedFileManager^ UnwrapCachedFileManager(Local<Value> value) {
     return CachedFileManager::Unwrap<CachedFileManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitCachedFileManager(Local<Object> exports) {
    CachedFileManager::Init(exports);
  }

  class SystemAudioProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemAudioProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("encodingBitrate").ToLocalChecked(), EncodingBitrateGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemAudioProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemAudioProperties(::Windows::Storage::SystemAudioProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SystemAudioProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemAudioProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SystemAudioProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemAudioProperties *wrapperInstance = new SystemAudioProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemAudioProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SystemAudioProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SystemAudioProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemAudioProperties(winRtInstance));
    }





    static void EncodingBitrateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemAudioProperties^>(info.This())) {
        return;
      }

      SystemAudioProperties *wrapper = SystemAudioProperties::Unwrap<SystemAudioProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->EncodingBitrate;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::SystemAudioProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemAudioProperties(::Windows::Storage::SystemAudioProperties^ wintRtInstance);
      friend ::Windows::Storage::SystemAudioProperties^ UnwrapSystemAudioProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemAudioProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemAudioProperties(::Windows::Storage::SystemAudioProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemAudioProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SystemAudioProperties^ UnwrapSystemAudioProperties(Local<Value> value) {
     return SystemAudioProperties::Unwrap<SystemAudioProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemAudioProperties(Local<Object> exports) {
    SystemAudioProperties::Init(exports);
  }

  class SystemGPSProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemGPSProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("latitudeDecimal").ToLocalChecked(), LatitudeDecimalGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("longitudeDecimal").ToLocalChecked(), LongitudeDecimalGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemGPSProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemGPSProperties(::Windows::Storage::SystemGPSProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SystemGPSProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemGPSProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SystemGPSProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemGPSProperties *wrapperInstance = new SystemGPSProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemGPSProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SystemGPSProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SystemGPSProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemGPSProperties(winRtInstance));
    }





    static void LatitudeDecimalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemGPSProperties^>(info.This())) {
        return;
      }

      SystemGPSProperties *wrapper = SystemGPSProperties::Unwrap<SystemGPSProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->LatitudeDecimal;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LongitudeDecimalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemGPSProperties^>(info.This())) {
        return;
      }

      SystemGPSProperties *wrapper = SystemGPSProperties::Unwrap<SystemGPSProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->LongitudeDecimal;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::SystemGPSProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemGPSProperties(::Windows::Storage::SystemGPSProperties^ wintRtInstance);
      friend ::Windows::Storage::SystemGPSProperties^ UnwrapSystemGPSProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemGPSProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemGPSProperties(::Windows::Storage::SystemGPSProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemGPSProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SystemGPSProperties^ UnwrapSystemGPSProperties(Local<Value> value) {
     return SystemGPSProperties::Unwrap<SystemGPSProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemGPSProperties(Local<Object> exports) {
    SystemGPSProperties::Init(exports);
  }

  class SystemImageProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemImageProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("horizontalSize").ToLocalChecked(), HorizontalSizeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("verticalSize").ToLocalChecked(), VerticalSizeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemImageProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemImageProperties(::Windows::Storage::SystemImageProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SystemImageProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemImageProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SystemImageProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemImageProperties *wrapperInstance = new SystemImageProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemImageProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SystemImageProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SystemImageProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemImageProperties(winRtInstance));
    }





    static void HorizontalSizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemImageProperties^>(info.This())) {
        return;
      }

      SystemImageProperties *wrapper = SystemImageProperties::Unwrap<SystemImageProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->HorizontalSize;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void VerticalSizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemImageProperties^>(info.This())) {
        return;
      }

      SystemImageProperties *wrapper = SystemImageProperties::Unwrap<SystemImageProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->VerticalSize;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::SystemImageProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemImageProperties(::Windows::Storage::SystemImageProperties^ wintRtInstance);
      friend ::Windows::Storage::SystemImageProperties^ UnwrapSystemImageProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemImageProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemImageProperties(::Windows::Storage::SystemImageProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemImageProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SystemImageProperties^ UnwrapSystemImageProperties(Local<Value> value) {
     return SystemImageProperties::Unwrap<SystemImageProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemImageProperties(Local<Object> exports) {
    SystemImageProperties::Init(exports);
  }

  class SystemMediaProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemMediaProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("duration").ToLocalChecked(), DurationGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("producer").ToLocalChecked(), ProducerGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("publisher").ToLocalChecked(), PublisherGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("subTitle").ToLocalChecked(), SubTitleGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("writer").ToLocalChecked(), WriterGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("year").ToLocalChecked(), YearGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemMediaProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemMediaProperties(::Windows::Storage::SystemMediaProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SystemMediaProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMediaProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SystemMediaProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemMediaProperties *wrapperInstance = new SystemMediaProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMediaProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SystemMediaProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SystemMediaProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemMediaProperties(winRtInstance));
    }





    static void DurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMediaProperties^>(info.This())) {
        return;
      }

      SystemMediaProperties *wrapper = SystemMediaProperties::Unwrap<SystemMediaProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Duration;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProducerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMediaProperties^>(info.This())) {
        return;
      }

      SystemMediaProperties *wrapper = SystemMediaProperties::Unwrap<SystemMediaProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Producer;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PublisherGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMediaProperties^>(info.This())) {
        return;
      }

      SystemMediaProperties *wrapper = SystemMediaProperties::Unwrap<SystemMediaProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Publisher;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SubTitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMediaProperties^>(info.This())) {
        return;
      }

      SystemMediaProperties *wrapper = SystemMediaProperties::Unwrap<SystemMediaProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->SubTitle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void WriterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMediaProperties^>(info.This())) {
        return;
      }

      SystemMediaProperties *wrapper = SystemMediaProperties::Unwrap<SystemMediaProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Writer;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void YearGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMediaProperties^>(info.This())) {
        return;
      }

      SystemMediaProperties *wrapper = SystemMediaProperties::Unwrap<SystemMediaProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Year;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::SystemMediaProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemMediaProperties(::Windows::Storage::SystemMediaProperties^ wintRtInstance);
      friend ::Windows::Storage::SystemMediaProperties^ UnwrapSystemMediaProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemMediaProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemMediaProperties(::Windows::Storage::SystemMediaProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemMediaProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SystemMediaProperties^ UnwrapSystemMediaProperties(Local<Value> value) {
     return SystemMediaProperties::Unwrap<SystemMediaProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemMediaProperties(Local<Object> exports) {
    SystemMediaProperties::Init(exports);
  }

  class SystemMusicProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemMusicProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("albumArtist").ToLocalChecked(), AlbumArtistGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("albumTitle").ToLocalChecked(), AlbumTitleGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("artist").ToLocalChecked(), ArtistGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("composer").ToLocalChecked(), ComposerGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("conductor").ToLocalChecked(), ConductorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayArtist").ToLocalChecked(), DisplayArtistGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("genre").ToLocalChecked(), GenreGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("trackNumber").ToLocalChecked(), TrackNumberGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemMusicProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemMusicProperties(::Windows::Storage::SystemMusicProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SystemMusicProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMusicProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SystemMusicProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemMusicProperties *wrapperInstance = new SystemMusicProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMusicProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SystemMusicProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SystemMusicProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemMusicProperties(winRtInstance));
    }





    static void AlbumArtistGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMusicProperties^>(info.This())) {
        return;
      }

      SystemMusicProperties *wrapper = SystemMusicProperties::Unwrap<SystemMusicProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->AlbumArtist;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AlbumTitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMusicProperties^>(info.This())) {
        return;
      }

      SystemMusicProperties *wrapper = SystemMusicProperties::Unwrap<SystemMusicProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->AlbumTitle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ArtistGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMusicProperties^>(info.This())) {
        return;
      }

      SystemMusicProperties *wrapper = SystemMusicProperties::Unwrap<SystemMusicProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Artist;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ComposerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMusicProperties^>(info.This())) {
        return;
      }

      SystemMusicProperties *wrapper = SystemMusicProperties::Unwrap<SystemMusicProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Composer;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ConductorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMusicProperties^>(info.This())) {
        return;
      }

      SystemMusicProperties *wrapper = SystemMusicProperties::Unwrap<SystemMusicProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Conductor;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DisplayArtistGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMusicProperties^>(info.This())) {
        return;
      }

      SystemMusicProperties *wrapper = SystemMusicProperties::Unwrap<SystemMusicProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayArtist;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void GenreGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMusicProperties^>(info.This())) {
        return;
      }

      SystemMusicProperties *wrapper = SystemMusicProperties::Unwrap<SystemMusicProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Genre;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TrackNumberGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemMusicProperties^>(info.This())) {
        return;
      }

      SystemMusicProperties *wrapper = SystemMusicProperties::Unwrap<SystemMusicProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->TrackNumber;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::SystemMusicProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemMusicProperties(::Windows::Storage::SystemMusicProperties^ wintRtInstance);
      friend ::Windows::Storage::SystemMusicProperties^ UnwrapSystemMusicProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemMusicProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemMusicProperties(::Windows::Storage::SystemMusicProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemMusicProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SystemMusicProperties^ UnwrapSystemMusicProperties(Local<Value> value) {
     return SystemMusicProperties::Unwrap<SystemMusicProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemMusicProperties(Local<Object> exports) {
    SystemMusicProperties::Init(exports);
  }

  class SystemPhotoProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemPhotoProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("cameraManufacturer").ToLocalChecked(), CameraManufacturerGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("cameraModel").ToLocalChecked(), CameraModelGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dateTaken").ToLocalChecked(), DateTakenGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("orientation").ToLocalChecked(), OrientationGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("peopleNames").ToLocalChecked(), PeopleNamesGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemPhotoProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemPhotoProperties(::Windows::Storage::SystemPhotoProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SystemPhotoProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemPhotoProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SystemPhotoProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemPhotoProperties *wrapperInstance = new SystemPhotoProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemPhotoProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SystemPhotoProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SystemPhotoProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemPhotoProperties(winRtInstance));
    }





    static void CameraManufacturerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemPhotoProperties^>(info.This())) {
        return;
      }

      SystemPhotoProperties *wrapper = SystemPhotoProperties::Unwrap<SystemPhotoProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->CameraManufacturer;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CameraModelGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemPhotoProperties^>(info.This())) {
        return;
      }

      SystemPhotoProperties *wrapper = SystemPhotoProperties::Unwrap<SystemPhotoProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->CameraModel;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DateTakenGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemPhotoProperties^>(info.This())) {
        return;
      }

      SystemPhotoProperties *wrapper = SystemPhotoProperties::Unwrap<SystemPhotoProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DateTaken;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OrientationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemPhotoProperties^>(info.This())) {
        return;
      }

      SystemPhotoProperties *wrapper = SystemPhotoProperties::Unwrap<SystemPhotoProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Orientation;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PeopleNamesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemPhotoProperties^>(info.This())) {
        return;
      }

      SystemPhotoProperties *wrapper = SystemPhotoProperties::Unwrap<SystemPhotoProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->PeopleNames;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::SystemPhotoProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemPhotoProperties(::Windows::Storage::SystemPhotoProperties^ wintRtInstance);
      friend ::Windows::Storage::SystemPhotoProperties^ UnwrapSystemPhotoProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemPhotoProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemPhotoProperties(::Windows::Storage::SystemPhotoProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemPhotoProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SystemPhotoProperties^ UnwrapSystemPhotoProperties(Local<Value> value) {
     return SystemPhotoProperties::Unwrap<SystemPhotoProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemPhotoProperties(Local<Object> exports) {
    SystemPhotoProperties::Init(exports);
  }

  class SystemVideoProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemVideoProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("director").ToLocalChecked(), DirectorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("frameHeight").ToLocalChecked(), FrameHeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("frameWidth").ToLocalChecked(), FrameWidthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("orientation").ToLocalChecked(), OrientationGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("totalBitrate").ToLocalChecked(), TotalBitrateGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SystemVideoProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemVideoProperties(::Windows::Storage::SystemVideoProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SystemVideoProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemVideoProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SystemVideoProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemVideoProperties *wrapperInstance = new SystemVideoProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemVideoProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SystemVideoProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SystemVideoProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemVideoProperties(winRtInstance));
    }





    static void DirectorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemVideoProperties^>(info.This())) {
        return;
      }

      SystemVideoProperties *wrapper = SystemVideoProperties::Unwrap<SystemVideoProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Director;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FrameHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemVideoProperties^>(info.This())) {
        return;
      }

      SystemVideoProperties *wrapper = SystemVideoProperties::Unwrap<SystemVideoProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FrameHeight;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FrameWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemVideoProperties^>(info.This())) {
        return;
      }

      SystemVideoProperties *wrapper = SystemVideoProperties::Unwrap<SystemVideoProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FrameWidth;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OrientationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemVideoProperties^>(info.This())) {
        return;
      }

      SystemVideoProperties *wrapper = SystemVideoProperties::Unwrap<SystemVideoProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Orientation;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TotalBitrateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemVideoProperties^>(info.This())) {
        return;
      }

      SystemVideoProperties *wrapper = SystemVideoProperties::Unwrap<SystemVideoProperties>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->TotalBitrate;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::SystemVideoProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemVideoProperties(::Windows::Storage::SystemVideoProperties^ wintRtInstance);
      friend ::Windows::Storage::SystemVideoProperties^ UnwrapSystemVideoProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemVideoProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemVideoProperties(::Windows::Storage::SystemVideoProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemVideoProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SystemVideoProperties^ UnwrapSystemVideoProperties(Local<Value> value) {
     return SystemVideoProperties::Unwrap<SystemVideoProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemVideoProperties(Local<Object> exports) {
    SystemVideoProperties::Init(exports);
  }

  class SystemProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SystemProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetAccessor(constructor, Nan::New<String>("audio").ToLocalChecked(), AudioGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("author").ToLocalChecked(), AuthorGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("comment").ToLocalChecked(), CommentGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gPS").ToLocalChecked(), GPSGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("image").ToLocalChecked(), ImageGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("itemNameDisplay").ToLocalChecked(), ItemNameDisplayGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("keywords").ToLocalChecked(), KeywordsGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("media").ToLocalChecked(), MediaGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("music").ToLocalChecked(), MusicGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("photo").ToLocalChecked(), PhotoGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("rating").ToLocalChecked(), RatingGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("title").ToLocalChecked(), TitleGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("video").ToLocalChecked(), VideoGetter);


        Nan::Set(exports, Nan::New<String>("SystemProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SystemProperties(::Windows::Storage::SystemProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SystemProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SystemProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SystemProperties *wrapperInstance = new SystemProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SystemProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SystemProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SystemProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSystemProperties(winRtInstance));
    }







    static void AudioGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::SystemAudioProperties^ result = ::Windows::Storage::SystemProperties::Audio;
        info.GetReturnValue().Set(WrapSystemAudioProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AuthorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Storage::SystemProperties::Author;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void CommentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Storage::SystemProperties::Comment;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GPSGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::SystemGPSProperties^ result = ::Windows::Storage::SystemProperties::GPS;
        info.GetReturnValue().Set(WrapSystemGPSProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ImageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::SystemImageProperties^ result = ::Windows::Storage::SystemProperties::Image;
        info.GetReturnValue().Set(WrapSystemImageProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ItemNameDisplayGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Storage::SystemProperties::ItemNameDisplay;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KeywordsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Storage::SystemProperties::Keywords;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MediaGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::SystemMediaProperties^ result = ::Windows::Storage::SystemProperties::Media;
        info.GetReturnValue().Set(WrapSystemMediaProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MusicGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::SystemMusicProperties^ result = ::Windows::Storage::SystemProperties::Music;
        info.GetReturnValue().Set(WrapSystemMusicProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PhotoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::SystemPhotoProperties^ result = ::Windows::Storage::SystemProperties::Photo;
        info.GetReturnValue().Set(WrapSystemPhotoProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void RatingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Storage::SystemProperties::Rating;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Storage::SystemProperties::Title;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void VideoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::SystemVideoProperties^ result = ::Windows::Storage::SystemProperties::Video;
        info.GetReturnValue().Set(WrapSystemVideoProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Storage::SystemProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSystemProperties(::Windows::Storage::SystemProperties^ wintRtInstance);
      friend ::Windows::Storage::SystemProperties^ UnwrapSystemProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> SystemProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapSystemProperties(::Windows::Storage::SystemProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SystemProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SystemProperties^ UnwrapSystemProperties(Local<Value> value) {
     return SystemProperties::Unwrap<SystemProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSystemProperties(Local<Object> exports) {
    SystemProperties::Init(exports);
  }

  class ApplicationData : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("ApplicationData").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "signalDataChanged", SignalDataChanged);
            Nan::SetPrototypeMethod(localRef, "getPublisherCacheFolder", GetPublisherCacheFolder);
          

          
            Nan::SetPrototypeMethod(localRef, "setVersionAsync", SetVersionAsync);
            Nan::SetPrototypeMethod(localRef, "clearAsync", ClearAsync);
            Nan::SetPrototypeMethod(localRef, "clearPublisherCacheFolderAsync", ClearPublisherCacheFolderAsync);
          

          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localFolder").ToLocalChecked(), LocalFolderGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localSettings").ToLocalChecked(), LocalSettingsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("roamingFolder").ToLocalChecked(), RoamingFolderGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("roamingSettings").ToLocalChecked(), RoamingSettingsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("roamingStorageQuota").ToLocalChecked(), RoamingStorageQuotaGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("temporaryFolder").ToLocalChecked(), TemporaryFolderGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("version").ToLocalChecked(), VersionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("localCacheFolder").ToLocalChecked(), LocalCacheFolderGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("sharedLocalFolder").ToLocalChecked(), SharedLocalFolderGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        func = Nan::GetFunction(Nan::New<FunctionTemplate>(GetForUserAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("getForUserAsync").ToLocalChecked(), func);
        Nan::SetAccessor(constructor, Nan::New<String>("current").ToLocalChecked(), CurrentGetter);


        Nan::Set(exports, Nan::New<String>("ApplicationData").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      ApplicationData(::Windows::Storage::ApplicationData^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::ApplicationData^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::ApplicationData^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ApplicationData *wrapperInstance = new ApplicationData(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::ApplicationData^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::ApplicationData^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapApplicationData(winRtInstance));
    }

    static void SetVersionAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 3
        && info[0]->IsUint32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataSetVersionHandler^>(info[1]))
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          ::Windows::Storage::ApplicationDataSetVersionHandler^ arg1 = dynamic_cast<::Windows::Storage::ApplicationDataSetVersionHandler^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          op = wrapper->_instance->SetVersionAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void ClearAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->ClearAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Storage::ApplicationDataLocality arg0 = static_cast<::Windows::Storage::ApplicationDataLocality>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->ClearAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }
    static void ClearPublisherCacheFolderAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          op = wrapper->_instance->ClearPublisherCacheFolderAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void SignalDataChanged(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->SignalDataChanged();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetPublisherCacheFolder(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Storage::StorageFolder^ result;
          result = wrapper->_instance->GetPublisherCacheFolder(arg0);
          info.GetReturnValue().Set(WrapStorageFolder(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }


    static void GetForUserAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Storage::ApplicationData^>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0]))
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
            
          op = ::Windows::Storage::ApplicationData::GetForUserAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Storage::ApplicationData^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapApplicationData(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void LocalFolderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      try  {
        ::Windows::Storage::StorageFolder^ result = wrapper->_instance->LocalFolder;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalSettingsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      try  {
        ::Windows::Storage::ApplicationDataContainer^ result = wrapper->_instance->LocalSettings;
        info.GetReturnValue().Set(WrapApplicationDataContainer(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RoamingFolderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      try  {
        ::Windows::Storage::StorageFolder^ result = wrapper->_instance->RoamingFolder;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RoamingSettingsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      try  {
        ::Windows::Storage::ApplicationDataContainer^ result = wrapper->_instance->RoamingSettings;
        info.GetReturnValue().Set(WrapApplicationDataContainer(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RoamingStorageQuotaGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      try  {
        unsigned __int64 result = wrapper->_instance->RoamingStorageQuota;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TemporaryFolderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      try  {
        ::Windows::Storage::StorageFolder^ result = wrapper->_instance->TemporaryFolder;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void VersionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Version;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalCacheFolderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      try  {
        ::Windows::Storage::StorageFolder^ result = wrapper->_instance->LocalCacheFolder;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SharedLocalFolderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This())) {
        return;
      }

      ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());

      try  {
        ::Windows::Storage::StorageFolder^ result = wrapper->_instance->SharedLocalFolder;
        info.GetReturnValue().Set(WrapStorageFolder(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void CurrentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Storage::ApplicationData^ result = ::Windows::Storage::ApplicationData::Current;
        info.GetReturnValue().Set(WrapApplicationData(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"dataChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->DataChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Storage::ApplicationData^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Storage::ApplicationData^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapApplicationData(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"dataChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"dataChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationData^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          ApplicationData *wrapper = ApplicationData::Unwrap<ApplicationData>(info.This());
          wrapper->_instance->DataChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Storage::ApplicationData^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapApplicationData(::Windows::Storage::ApplicationData^ wintRtInstance);
      friend ::Windows::Storage::ApplicationData^ UnwrapApplicationData(Local<Value> value);
  };

  Persistent<FunctionTemplate> ApplicationData::s_constructorTemplate;

  v8::Local<v8::Value> WrapApplicationData(::Windows::Storage::ApplicationData^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ApplicationData::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::ApplicationData^ UnwrapApplicationData(Local<Value> value) {
     return ApplicationData::Unwrap<ApplicationData>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitApplicationData(Local<Object> exports) {
    ApplicationData::Init(exports);
  }

  class SetVersionRequest : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SetVersionRequest").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("currentVersion").ToLocalChecked(), CurrentVersionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("desiredVersion").ToLocalChecked(), DesiredVersionGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SetVersionRequest").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SetVersionRequest(::Windows::Storage::SetVersionRequest^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SetVersionRequest^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SetVersionRequest^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SetVersionRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SetVersionRequest *wrapperInstance = new SetVersionRequest(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SetVersionRequest^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SetVersionRequest^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SetVersionRequest^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSetVersionRequest(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SetVersionRequest^>(info.This())) {
        return;
      }

      SetVersionRequest *wrapper = SetVersionRequest::Unwrap<SetVersionRequest>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::SetVersionDeferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(WrapSetVersionDeferral(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void CurrentVersionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SetVersionRequest^>(info.This())) {
        return;
      }

      SetVersionRequest *wrapper = SetVersionRequest::Unwrap<SetVersionRequest>(info.This());

      try  {
        unsigned int result = wrapper->_instance->CurrentVersion;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DesiredVersionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SetVersionRequest^>(info.This())) {
        return;
      }

      SetVersionRequest *wrapper = SetVersionRequest::Unwrap<SetVersionRequest>(info.This());

      try  {
        unsigned int result = wrapper->_instance->DesiredVersion;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::SetVersionRequest^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSetVersionRequest(::Windows::Storage::SetVersionRequest^ wintRtInstance);
      friend ::Windows::Storage::SetVersionRequest^ UnwrapSetVersionRequest(Local<Value> value);
  };

  Persistent<FunctionTemplate> SetVersionRequest::s_constructorTemplate;

  v8::Local<v8::Value> WrapSetVersionRequest(::Windows::Storage::SetVersionRequest^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SetVersionRequest::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SetVersionRequest^ UnwrapSetVersionRequest(Local<Value> value) {
     return SetVersionRequest::Unwrap<SetVersionRequest>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSetVersionRequest(Local<Object> exports) {
    SetVersionRequest::Init(exports);
  }

  class ApplicationDataContainer : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("ApplicationDataContainer").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "createContainer", CreateContainer);
            Nan::SetPrototypeMethod(localRef, "deleteContainer", DeleteContainer);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("containers").ToLocalChecked(), ContainersGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("locality").ToLocalChecked(), LocalityGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("name").ToLocalChecked(), NameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("values").ToLocalChecked(), ValuesGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("ApplicationDataContainer").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      ApplicationDataContainer(::Windows::Storage::ApplicationDataContainer^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::ApplicationDataContainer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainer^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::ApplicationDataContainer^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ApplicationDataContainer *wrapperInstance = new ApplicationDataContainer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainer^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::ApplicationDataContainer^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::ApplicationDataContainer^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapApplicationDataContainer(winRtInstance));
    }


    static void CreateContainer(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainer^>(info.This())) {
        return;
      }

      ApplicationDataContainer *wrapper = ApplicationDataContainer::Unwrap<ApplicationDataContainer>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsInt32())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Storage::ApplicationDataCreateDisposition arg1 = static_cast<::Windows::Storage::ApplicationDataCreateDisposition>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          ::Windows::Storage::ApplicationDataContainer^ result;
          result = wrapper->_instance->CreateContainer(arg0, arg1);
          info.GetReturnValue().Set(WrapApplicationDataContainer(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DeleteContainer(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainer^>(info.This())) {
        return;
      }

      ApplicationDataContainer *wrapper = ApplicationDataContainer::Unwrap<ApplicationDataContainer>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->DeleteContainer(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void ContainersGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainer^>(info.This())) {
        return;
      }

      ApplicationDataContainer *wrapper = ApplicationDataContainer::Unwrap<ApplicationDataContainer>(info.This());

      try  {
        ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Windows::Storage::ApplicationDataContainer^>^ result = wrapper->_instance->Containers;
        info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Windows::Storage::ApplicationDataContainer^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            },
            [](::Windows::Storage::ApplicationDataContainer^ val) -> Local<Value> {
              return WrapApplicationDataContainer(val);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LocalityGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainer^>(info.This())) {
        return;
      }

      ApplicationDataContainer *wrapper = ApplicationDataContainer::Unwrap<ApplicationDataContainer>(info.This());

      try  {
        ::Windows::Storage::ApplicationDataLocality result = wrapper->_instance->Locality;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainer^>(info.This())) {
        return;
      }

      ApplicationDataContainer *wrapper = ApplicationDataContainer::Unwrap<ApplicationDataContainer>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Name;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ValuesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainer^>(info.This())) {
        return;
      }

      ApplicationDataContainer *wrapper = ApplicationDataContainer::Unwrap<ApplicationDataContainer>(info.This());

      try  {
        ::Windows::Foundation::Collections::IPropertySet^ result = wrapper->_instance->Values;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IPropertySet", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Storage::ApplicationDataContainer^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapApplicationDataContainer(::Windows::Storage::ApplicationDataContainer^ wintRtInstance);
      friend ::Windows::Storage::ApplicationDataContainer^ UnwrapApplicationDataContainer(Local<Value> value);
  };

  Persistent<FunctionTemplate> ApplicationDataContainer::s_constructorTemplate;

  v8::Local<v8::Value> WrapApplicationDataContainer(::Windows::Storage::ApplicationDataContainer^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ApplicationDataContainer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::ApplicationDataContainer^ UnwrapApplicationDataContainer(Local<Value> value) {
     return ApplicationDataContainer::Unwrap<ApplicationDataContainer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitApplicationDataContainer(Local<Object> exports) {
    ApplicationDataContainer::Init(exports);
  }

  class SetVersionDeferral : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SetVersionDeferral").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "complete", Complete);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("SetVersionDeferral").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SetVersionDeferral(::Windows::Storage::SetVersionDeferral^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::SetVersionDeferral^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SetVersionDeferral^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::SetVersionDeferral^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      SetVersionDeferral *wrapperInstance = new SetVersionDeferral(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SetVersionDeferral^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::SetVersionDeferral^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::SetVersionDeferral^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSetVersionDeferral(winRtInstance));
    }


    static void Complete(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::SetVersionDeferral^>(info.This())) {
        return;
      }

      SetVersionDeferral *wrapper = SetVersionDeferral::Unwrap<SetVersionDeferral>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Complete();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Storage::SetVersionDeferral^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSetVersionDeferral(::Windows::Storage::SetVersionDeferral^ wintRtInstance);
      friend ::Windows::Storage::SetVersionDeferral^ UnwrapSetVersionDeferral(Local<Value> value);
  };

  Persistent<FunctionTemplate> SetVersionDeferral::s_constructorTemplate;

  v8::Local<v8::Value> WrapSetVersionDeferral(::Windows::Storage::SetVersionDeferral^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SetVersionDeferral::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::SetVersionDeferral^ UnwrapSetVersionDeferral(Local<Value> value) {
     return SetVersionDeferral::Unwrap<SetVersionDeferral>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSetVersionDeferral(Local<Object> exports) {
    SetVersionDeferral::Init(exports);
  }

  class ApplicationDataContainerSettings : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("ApplicationDataContainerSettings").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "lookup", Lookup);
            Nan::SetPrototypeMethod(localRef, "hasKey", HasKey);
            Nan::SetPrototypeMethod(localRef, "getView", GetView);
            Nan::SetPrototypeMethod(localRef, "insert", Insert);
            Nan::SetPrototypeMethod(localRef, "remove", Remove);
            Nan::SetPrototypeMethod(localRef, "clear", Clear);
            Nan::SetPrototypeMethod(localRef, "first", First);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);


        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("ApplicationDataContainerSettings").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      ApplicationDataContainerSettings(::Windows::Storage::ApplicationDataContainerSettings^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::ApplicationDataContainerSettings^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::ApplicationDataContainerSettings^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ApplicationDataContainerSettings *wrapperInstance = new ApplicationDataContainerSettings(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::ApplicationDataContainerSettings^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::ApplicationDataContainerSettings^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapApplicationDataContainerSettings(winRtInstance));
    }


    static void Lookup(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info.This())) {
        return;
      }

      ApplicationDataContainerSettings *wrapper = ApplicationDataContainerSettings::Unwrap<ApplicationDataContainerSettings>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Platform::Object^ result;
          result = wrapper->_instance->Lookup(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void HasKey(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info.This())) {
        return;
      }

      ApplicationDataContainerSettings *wrapper = ApplicationDataContainerSettings::Unwrap<ApplicationDataContainerSettings>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          bool result;
          result = wrapper->_instance->HasKey(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetView(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info.This())) {
        return;
      }

      ApplicationDataContainerSettings *wrapper = ApplicationDataContainerSettings::Unwrap<ApplicationDataContainerSettings>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Platform::Object^>^ result;
          result = wrapper->_instance->GetView();
          info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Platform::Object^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            },
            [](::Platform::Object^ val) -> Local<Value> {
              return CreateOpaqueWrapper(val);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Insert(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info.This())) {
        return;
      }

      ApplicationDataContainerSettings *wrapper = ApplicationDataContainerSettings::Unwrap<ApplicationDataContainerSettings>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          bool result;
          result = wrapper->_instance->Insert(arg0, arg1);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Remove(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info.This())) {
        return;
      }

      ApplicationDataContainerSettings *wrapper = ApplicationDataContainerSettings::Unwrap<ApplicationDataContainerSettings>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->Remove(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Clear(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info.This())) {
        return;
      }

      ApplicationDataContainerSettings *wrapper = ApplicationDataContainerSettings::Unwrap<ApplicationDataContainerSettings>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Clear();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void First(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info.This())) {
        return;
      }

      ApplicationDataContainerSettings *wrapper = ApplicationDataContainerSettings::Unwrap<ApplicationDataContainerSettings>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Platform::Object^>^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Platform::Object^>^>::CreateIteratorWrapper(result, 
            [](::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Platform::Object^>^ val) -> Local<Value> {
              return NodeRT::Collections::KeyValuePairWrapper<::Platform::String^,::Platform::Object^>::CreateKeyValuePairWrapper(val, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](::Platform::Object^ val) -> Local<Value> {
              return CreateOpaqueWrapper(val);
            }
          );
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"mapChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        ApplicationDataContainerSettings *wrapper = ApplicationDataContainerSettings::Unwrap<ApplicationDataContainerSettings>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->MapChanged::add(
            ref new ::Windows::Foundation::Collections::MapChangedEventHandler<::Platform::String^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Foundation::Collections::IObservableMap<::Platform::String^, ::Platform::Object^>^ arg0, ::Windows::Foundation::Collections::IMapChangedEventArgs<::Platform::String^>^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IObservableMap`2", arg0);
                  wrappedArg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IMapChangedEventArgs`1", arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"mapChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"mapChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataContainerSettings^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          ApplicationDataContainerSettings *wrapper = ApplicationDataContainerSettings::Unwrap<ApplicationDataContainerSettings>(info.This());
          wrapper->_instance->MapChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Storage::ApplicationDataContainerSettings^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapApplicationDataContainerSettings(::Windows::Storage::ApplicationDataContainerSettings^ wintRtInstance);
      friend ::Windows::Storage::ApplicationDataContainerSettings^ UnwrapApplicationDataContainerSettings(Local<Value> value);
  };

  Persistent<FunctionTemplate> ApplicationDataContainerSettings::s_constructorTemplate;

  v8::Local<v8::Value> WrapApplicationDataContainerSettings(::Windows::Storage::ApplicationDataContainerSettings^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ApplicationDataContainerSettings::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::ApplicationDataContainerSettings^ UnwrapApplicationDataContainerSettings(Local<Value> value) {
     return ApplicationDataContainerSettings::Unwrap<ApplicationDataContainerSettings>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitApplicationDataContainerSettings(Local<Object> exports) {
    ApplicationDataContainerSettings::Init(exports);
  }

  class ApplicationDataCompositeValue : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("ApplicationDataCompositeValue").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "lookup", Lookup);
            Nan::SetPrototypeMethod(localRef, "hasKey", HasKey);
            Nan::SetPrototypeMethod(localRef, "getView", GetView);
            Nan::SetPrototypeMethod(localRef, "insert", Insert);
            Nan::SetPrototypeMethod(localRef, "remove", Remove);
            Nan::SetPrototypeMethod(localRef, "clear", Clear);
            Nan::SetPrototypeMethod(localRef, "first", First);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);


        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("ApplicationDataCompositeValue").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      ApplicationDataCompositeValue(::Windows::Storage::ApplicationDataCompositeValue^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Storage::ApplicationDataCompositeValue^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info[0])) {
        try {
          winRtInstance = (::Windows::Storage::ApplicationDataCompositeValue^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Storage::ApplicationDataCompositeValue();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ApplicationDataCompositeValue *wrapperInstance = new ApplicationDataCompositeValue(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Storage::ApplicationDataCompositeValue^ winRtInstance;
      try {
        winRtInstance = (::Windows::Storage::ApplicationDataCompositeValue^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapApplicationDataCompositeValue(winRtInstance));
    }


    static void Lookup(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info.This())) {
        return;
      }

      ApplicationDataCompositeValue *wrapper = ApplicationDataCompositeValue::Unwrap<ApplicationDataCompositeValue>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Platform::Object^ result;
          result = wrapper->_instance->Lookup(arg0);
          info.GetReturnValue().Set(CreateOpaqueWrapper(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void HasKey(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info.This())) {
        return;
      }

      ApplicationDataCompositeValue *wrapper = ApplicationDataCompositeValue::Unwrap<ApplicationDataCompositeValue>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          bool result;
          result = wrapper->_instance->HasKey(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetView(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info.This())) {
        return;
      }

      ApplicationDataCompositeValue *wrapper = ApplicationDataCompositeValue::Unwrap<ApplicationDataCompositeValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Platform::Object^>^ result;
          result = wrapper->_instance->GetView();
          info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Platform::Object^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            },
            [](::Platform::Object^ val) -> Local<Value> {
              return CreateOpaqueWrapper(val);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Insert(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info.This())) {
        return;
      }

      ApplicationDataCompositeValue *wrapper = ApplicationDataCompositeValue::Unwrap<ApplicationDataCompositeValue>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Platform::Object^ arg1 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          bool result;
          result = wrapper->_instance->Insert(arg0, arg1);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Remove(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info.This())) {
        return;
      }

      ApplicationDataCompositeValue *wrapper = ApplicationDataCompositeValue::Unwrap<ApplicationDataCompositeValue>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->Remove(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Clear(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info.This())) {
        return;
      }

      ApplicationDataCompositeValue *wrapper = ApplicationDataCompositeValue::Unwrap<ApplicationDataCompositeValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Clear();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void First(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info.This())) {
        return;
      }

      ApplicationDataCompositeValue *wrapper = ApplicationDataCompositeValue::Unwrap<ApplicationDataCompositeValue>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Platform::Object^>^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Platform::Object^>^>::CreateIteratorWrapper(result, 
            [](::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Platform::Object^>^ val) -> Local<Value> {
              return NodeRT::Collections::KeyValuePairWrapper<::Platform::String^,::Platform::Object^>::CreateKeyValuePairWrapper(val, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](::Platform::Object^ val) -> Local<Value> {
              return CreateOpaqueWrapper(val);
            }
          );
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"mapChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        ApplicationDataCompositeValue *wrapper = ApplicationDataCompositeValue::Unwrap<ApplicationDataCompositeValue>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->MapChanged::add(
            ref new ::Windows::Foundation::Collections::MapChangedEventHandler<::Platform::String^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Foundation::Collections::IObservableMap<::Platform::String^, ::Platform::Object^>^ arg0, ::Windows::Foundation::Collections::IMapChangedEventArgs<::Platform::String^>^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IObservableMap`2", arg0);
                  wrappedArg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IMapChangedEventArgs`1", arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"mapChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"mapChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::ApplicationDataCompositeValue^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          ApplicationDataCompositeValue *wrapper = ApplicationDataCompositeValue::Unwrap<ApplicationDataCompositeValue>(info.This());
          wrapper->_instance->MapChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Storage::ApplicationDataCompositeValue^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapApplicationDataCompositeValue(::Windows::Storage::ApplicationDataCompositeValue^ wintRtInstance);
      friend ::Windows::Storage::ApplicationDataCompositeValue^ UnwrapApplicationDataCompositeValue(Local<Value> value);
  };

  Persistent<FunctionTemplate> ApplicationDataCompositeValue::s_constructorTemplate;

  v8::Local<v8::Value> WrapApplicationDataCompositeValue(::Windows::Storage::ApplicationDataCompositeValue^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ApplicationDataCompositeValue::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Storage::ApplicationDataCompositeValue^ UnwrapApplicationDataCompositeValue(Local<Value> value) {
     return ApplicationDataCompositeValue::Unwrap<ApplicationDataCompositeValue>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitApplicationDataCompositeValue(Local<Object> exports) {
    ApplicationDataCompositeValue::Init(exports);
  }


} } } 

NAN_MODULE_INIT(init) {
  // We ignore failures for now since it probably means that
  // the initialization already happened for STA, and that's cool

  CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  /*
  if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }
  */

      NodeRT::Windows::Storage::InitKnownLibraryIdEnum(target);
      NodeRT::Windows::Storage::InitKnownFolderIdEnum(target);
      NodeRT::Windows::Storage::InitCreationCollisionOptionEnum(target);
      NodeRT::Windows::Storage::InitNameCollisionOptionEnum(target);
      NodeRT::Windows::Storage::InitStorageDeleteOptionEnum(target);
      NodeRT::Windows::Storage::InitStorageItemTypesEnum(target);
      NodeRT::Windows::Storage::InitFileAttributesEnum(target);
      NodeRT::Windows::Storage::InitFileAccessModeEnum(target);
      NodeRT::Windows::Storage::InitStorageLibraryChangeTypeEnum(target);
      NodeRT::Windows::Storage::InitStreamedFileFailureModeEnum(target);
      NodeRT::Windows::Storage::InitStorageOpenOptionsEnum(target);
      NodeRT::Windows::Storage::InitApplicationDataLocalityEnum(target);
      NodeRT::Windows::Storage::InitApplicationDataCreateDispositionEnum(target);
      NodeRT::Windows::Storage::InitStorageLibrary(target);
      NodeRT::Windows::Storage::InitStorageFolder(target);
      NodeRT::Windows::Storage::InitStorageLibraryChangeTracker(target);
      NodeRT::Windows::Storage::InitKnownFolders(target);
      NodeRT::Windows::Storage::InitUserDataPaths(target);
      NodeRT::Windows::Storage::InitAppDataPaths(target);
      NodeRT::Windows::Storage::InitSystemDataPaths(target);
      NodeRT::Windows::Storage::InitStorageFile(target);
      NodeRT::Windows::Storage::InitDownloadsFolder(target);
      NodeRT::Windows::Storage::InitIStorageItem(target);
      NodeRT::Windows::Storage::InitStorageLibraryChange(target);
      NodeRT::Windows::Storage::InitStorageLibraryChangeReader(target);
      NodeRT::Windows::Storage::InitIStreamedFileDataRequest(target);
      NodeRT::Windows::Storage::InitStreamedFileDataRequest(target);
      NodeRT::Windows::Storage::InitStorageStreamTransaction(target);
      NodeRT::Windows::Storage::InitIStorageFolder(target);
      NodeRT::Windows::Storage::InitIStorageFile(target);
      NodeRT::Windows::Storage::InitIStorageItem2(target);
      NodeRT::Windows::Storage::InitIStorageItemProperties(target);
      NodeRT::Windows::Storage::InitIStorageItemProperties2(target);
      NodeRT::Windows::Storage::InitIStorageItemPropertiesWithProvider(target);
      NodeRT::Windows::Storage::InitStorageProvider(target);
      NodeRT::Windows::Storage::InitIStorageFilePropertiesWithAvailability(target);
      NodeRT::Windows::Storage::InitIStorageFolder2(target);
      NodeRT::Windows::Storage::InitIStorageFile2(target);
      NodeRT::Windows::Storage::InitFileIO(target);
      NodeRT::Windows::Storage::InitPathIO(target);
      NodeRT::Windows::Storage::InitCachedFileManager(target);
      NodeRT::Windows::Storage::InitSystemAudioProperties(target);
      NodeRT::Windows::Storage::InitSystemGPSProperties(target);
      NodeRT::Windows::Storage::InitSystemImageProperties(target);
      NodeRT::Windows::Storage::InitSystemMediaProperties(target);
      NodeRT::Windows::Storage::InitSystemMusicProperties(target);
      NodeRT::Windows::Storage::InitSystemPhotoProperties(target);
      NodeRT::Windows::Storage::InitSystemVideoProperties(target);
      NodeRT::Windows::Storage::InitSystemProperties(target);
      NodeRT::Windows::Storage::InitApplicationData(target);
      NodeRT::Windows::Storage::InitSetVersionRequest(target);
      NodeRT::Windows::Storage::InitApplicationDataContainer(target);
      NodeRT::Windows::Storage::InitSetVersionDeferral(target);
      NodeRT::Windows::Storage::InitApplicationDataContainerSettings(target);
      NodeRT::Windows::Storage::InitApplicationDataCompositeValue(target);


  NodeRT::Utils::RegisterNameSpace("Windows.Storage", target);
}



NODE_MODULE(binding, init)
