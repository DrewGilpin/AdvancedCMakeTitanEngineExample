/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
namespace Edit{
/******************************************************************************/
enum EXE_TYPE : Byte // Executable Type
{
   EXE_EXE  , // Windows Executable
   EXE_DLL  , // Windows Dynamically Linked Library
   EXE_LIB  , // Windows Statically  Linked Library (currently not supported, reserved for future use)
   EXE_UWP  , // Windows Universal App
   EXE_APK  , // Android Application Package
   EXE_AAB  , // Android Application Bundle
   EXE_MAC  , // Mac     Application
   EXE_IOS  , // iOS     Application
   EXE_LINUX, // Linux
   EXE_NS   , // Nintendo Switch
   EXE_WEB  , // Web     Html/JavaScript
   EXE_NUM  ,
};
enum EXPORT_MODE : Byte // Export Mode
{
   EXPORT_EXE           , // Export to project according to current Executable Type
   EXPORT_TXT           , // Export to text files
   EXPORT_CPP           , // Export to C++  files
   EXPORT_VS            , // Export to Visual Studio version that is currently selected in the Editor
   EXPORT_VS2015        , // Export to Visual Studio 2015 project
   EXPORT_VS2017        , // Export to Visual Studio 2017 project
   EXPORT_VS2019        , // Export to Visual Studio 2019 project
   EXPORT_VS2022        , // Export to Visual Studio 2022 project
   EXPORT_ANDROID       , // Export to Android            project
   EXPORT_XCODE         , // Export to Xcode              project
   EXPORT_LINUX_MAKE    , // Export to Linux              project to be compiled using 'make'
   EXPORT_LINUX_NETBEANS, // Export to Linux              project to be compiled using NetBeans
};
enum BUILD_MODE : Byte
{
   BUILD_EXPORT , // activated through "Build/Export"
   BUILD_IDE    , // activated through "Build/OpenInIDE"
   BUILD_PLAY   , // activated through "Play"                (Debug/Release)
   BUILD_DEBUG  , // activated through "Build/Debug"         (Debug/Release)
   BUILD_BUILD  , // activated through "Build/Build,Rebuild" (Debug/Release)
   BUILD_PUBLISH, // activated through "Build/Publish"       (      Release)
};
enum STORAGE_MODE : Byte
{
   STORAGE_INTERNAL,
   STORAGE_EXTERNAL,
   STORAGE_AUTO    ,
};
enum XBOX_LIVE : Byte // https://docs.microsoft.com/en-us/gaming/xbox-live/get-started/join-dev-program/live-dev-program-overview
{
   XBOX_LIVE_CREATORS,
   XBOX_LIVE_ID_XBOX , // ID@Xbox, Managed Partners
   XBOX_LIVE_NUM     ,
};
struct CodeEditorInterface
{
   Int android_asset_packs=-1; // -1=not using asset packs

   void del        ();
   void clear      ();
   void create     (GuiObj &parent, Bool menu_on_top);
   void update     (Bool active);
   void draw       ();
   void resize     ();
   void skinChanged();
   Bool initialized();
   Str  title      ();
   Str  appPath    (C Str &app_name);
   Str   androidPath();
   Str   androidProjectPakPath();
   Str       iOSProjectPakPath();
   Str       UWPProjectPakPath();
   Str  nintendoProjectPakPath();
   void saveChanges();
   void saveChanges(Memc<Edit::SaveChanges::Elm> &elms);
   void saveChanges(Memc<Edit::SaveChanges::Elm> &elms, void (*after_save_close)(Bool all_saved, Ptr user), Ptr user=null);
   void sourceRename     (C UID &id  ); // call this when source code file was renamed in the project
   Bool sourceCur        (C Str &name); // set current source
   Bool sourceCur        (C UID &id  ); // set current source
   Bool sourceCurIs      (           ); // if there is a current source
   Str  sourceCurName    (           ); // get current source
   UID  sourceCurId      (           ); // get current source
   Bool sourceCurModified(           ); // get current source modified state
   Bool sourceCurConst   (           ); // get current source const    state
   void sourceDrawPreview(C Str &name); // draw preview of source
   void sourceDrawPreview(C UID &id  ); // draw preview of source
   void sourceAuto       (C Str &data); // set data of the automatically generated source
   void sourceRemove     (C UID &id  ); // remove selected source
   void sourceOverwrite  (C UID &id  ); // overwrite any changes of selected source
   Bool sourceDataGet    (C UID &id,   Str &data); // get source data, false if source is not loaded
   Bool sourceDataSet    (C UID &id, C Str &data); // set source data, false if source is not loaded
   void projectsBuildPath(C Str &path); // set build path of all projects
   void menuEnabled         (Bool on);
   void kbSet               ();
   void close               ();
   void closeAll            ();
   void  hideAll            ();
   Bool visibleOptions      ();
   void visibleOptions      (Bool on);
   Bool visibleOpenedFiles  ();
   void visibleOpenedFiles  (Bool on);
   Bool visibleOutput       ();
   void visibleOutput       (Bool on);
   Bool visibleAndroidDevLog();
   void visibleAndroidDevLog(Bool on);

   Bool importPaths       ()C;
   Bool importImageMipMaps()C;

   void saveSettings(  TextNode &code);
   void loadSettings(C TextNode &code);

   void clearActiveSources(); // set all sources to be inactive (this must be called when changing app)
   void activateSource(C UID &id   ); // make project based source active
   void activateSource(C Str &name ); // make file    based source active
   void activateApp   (Bool rebuild); // finalize changing app

   void paste(C CMemPtr<UID> &elms, GuiObj *obj, C Vec2 &screen_pos); // paste project elements at specified position
   void paste(C Str &text         , GuiObj *obj, C Vec2 &screen_pos); // paste text             at specified position
   void paste(C Str &text                                          ); // paste text             at current   position

 C Memx<Item>& items(); // get Engine items

   void        play();
   void       debug();
   void runToCursor();
   void     publish();
   void       build();
   void     rebuild();
   void     rebuildSymbols();
   void       clean();
   void    cleanAll();
   void        stop();
   void     openIDE();
   void exportPaths(Bool relative);
   Bool      Export(EXPORT_MODE mode);

   void     configDebug(Bool     debug);
   Bool     configDebug(              );
   void     config32Bit(Bool     bit32);
   Bool     config32Bit(              );
   void     configAPI  (Byte     api  );
   Byte     configAPI  (              );
   void     configEXE  (EXE_TYPE exe  );
   EXE_TYPE configEXE  (              );

   virtual void visibleChangedOptions      () {}
   virtual void visibleChangedOpenedFiles  () {}
   virtual void visibleChangedOutput       () {}
   virtual void visibleChangedAndroidDevLog() {}

   virtual void configChangedDebug() {}
   virtual void configChanged32Bit() {}
   virtual void configChangedAPI  () {}
   virtual void configChangedEXE  () {}

   virtual UID projectID() {return UIDZero;} // get active Project ID

   virtual UID           appID                              () {return            UIDZero;} // get ID                                  of current app
   virtual Str           appName                            () {return                  S;} // get name                                of current app
   virtual Str           appDirsWindows                     () {return                  S;} // get all directories                     of current app
   virtual Str           appDirsMac                         () {return                  S;} // get all directories                     of current app
   virtual Str           appDirsLinux                       () {return                  S;} // get all directories                     of current app
   virtual Str           appDirsAndroid                     () {return                  S;} // get all directories                     of current app
   virtual Str           appDirsiOS                         () {return                  S;} // get all directories                     of current app
   virtual Str           appDirsNintendo                    () {return                  S;} // get all directories                     of current app
   virtual Str           appDirsWeb                         () {return                  S;} // get all directories                     of current app
   virtual Str           appHeadersWindows                  () {return                  S;} // get all headers                         of current app
   virtual Str           appHeadersMac                      () {return                  S;} // get all headers                         of current app
   virtual Str           appHeadersLinux                    () {return                  S;} // get all headers                         of current app
   virtual Str           appHeadersAndroid                  () {return                  S;} // get all headers                         of current app
   virtual Str           appHeadersiOS                      () {return                  S;} // get all headers                         of current app
   virtual Str           appHeadersNintendo                 () {return                  S;} // get all headers                         of current app
   virtual Str           appHeadersWeb                      () {return                  S;} // get all headers                         of current app
   virtual Str           appLibsWindows                     () {return                  S;} // get all libraries                       of current app
   virtual Str           appLibsMac                         () {return                  S;} // get all libraries                       of current app
   virtual Str           appLibsLinux                       () {return                  S;} // get all libraries                       of current app
   virtual Str           appLibsAndroid                     () {return                  S;} // get all libraries                       of current app
   virtual Str           appLibsiOS                         () {return                  S;} // get all libraries                       of current app
   virtual Str           appLibsNintendo                    () {return                  S;} // get all libraries                       of current app
   virtual Str           appLibsWeb                         () {return                  S;} // get all libraries                       of current app
   virtual Str           appPackage                         () {return                  S;} // get package name                        of current app
   virtual UID           appMicrosoftPublisherID            () {return            UIDZero;} // get Microsoft Publisher ID              of current app
   virtual Str           appMicrosoftPublisherName          () {return                  S;} // get Microsoft Publisher Name            of current app
   virtual XBOX_LIVE     appXboxLiveProgram                 () {return XBOX_LIVE_CREATORS;} // get Xbox Live program                   of current app
   virtual ULong         appXboxLiveTitleID                 () {return                  0;} // get Xbox Live Title ID                  of current app
   virtual UID           appXboxLiveSCID                    () {return            UIDZero;} // get Xbox Live SCID                      of current app
   virtual Bool          appWindowsCodeSign                 () {return              false;} // get if code sign exe                    of current app
   virtual Str           appGooglePlayLicenseKey            () {return                  S;} // get Google Play license key             of current app
   virtual Bool          appGooglePlayAssetDelivery         () {return              false;} // get Google Play Asset Delivery          of current app
   virtual Str           appLocationUsageReason             () {return                  S;} // get location usage reason               of current app
   virtual Str           appNintendoInitialCode             () {return                  S;} // get Nintendo Initial Code               of current app
   virtual ULong         appNintendoAppID                   () {return                  0;} // get Nintendo App ID                     of current app
   virtual Str           appNintendoPublisherName           () {return                  S;} // get Nintendo Publisher Name             of current app
   virtual Str           appNintendoLegalInformation        () {return                  S;} // get Nintendo Legal Information          of current app
   virtual Int           appBuild                           () {return                  1;} // get build number                        of current app
   virtual ULong         appFacebookAppID                   () {return                  0;} // get Facebook   App ID                   of current app
   virtual Str           appAdMobAppIDiOS                   () {return                  S;} // get AdMob      App ID                   of current app for iOS         platform
   virtual Str           appAdMobAppIDGooglePlay            () {return                  S;} // get AdMob      App ID                   of current app for Google Play platform
   virtual Str           appChartboostAppIDiOS              () {return                  S;} // get Chartboost App ID                   of current app for iOS         platform
   virtual Str           appChartboostAppSignatureiOS       () {return                  S;} // get Chartboost App Signature            of current app for iOS         platform
   virtual Str           appChartboostAppIDGooglePlay       () {return                  S;} // get Chartboost App ID                   of current app for Google Play platform
   virtual Str           appChartboostAppSignatureGooglePlay() {return                  S;} // get Chartboost App Signature            of current app for Google Play platform
   virtual STORAGE_MODE  appPreferredStorage                () {return   STORAGE_INTERNAL;} // get preferred storage                   of current app
   virtual UInt          appSupportedOrientations           () {return                  0;} // get supported orientations (DIR_FLAG)   of current app
   virtual UID           appGuiSkin                         () {return            UIDZero;} // get default Gui Skin                    of current app
   virtual ImagePtr      appIcon                            () {return               null;} // get icon                                of current app
   virtual ImagePtr      appImagePortrait                   () {return               null;} // get portrait  splash screen             of current app
   virtual ImagePtr      appImageLandscape                  () {return               null;} // get landscape splash screen             of current app
   virtual ImagePtr      appNotificationIcon                () {return               null;} // get notification icon                   of current app
   virtual Int           appEmbedEngineData                 () {return                  0;} // get if embed   engine  data             of current app
   virtual Cipher*       appEmbedCipher                     () {return               null;} // get cipher      used for embedding data of current app
   virtual Bool          appPublishProjData                 () {return               true;} // get if publish project data             of current app
   virtual Bool          appPublishPhysxDll                 () {return               true;} // get if copy PhysX  dll's                of current app
   virtual Bool          appPublishSteamDll                 () {return              false;} // get if copy Steam  dll                  of current app
   virtual Bool          appPublishOpenVRDll                () {return              false;} // get if copy OpenVR dll                  of current app
   virtual Bool          appPublishDataAsPak                () {return               true;} // get if publish data as paks             of current app
   virtual Long          appSaveSize                        () {return                 -1;} // get max save disk usage                 of current app
   virtual void          appInvalidProperty                 (C Str &msg                                  ) {                         } // called when application property was detected as invalid
   virtual COMPRESS_TYPE appEmbedCompress                   (                           EXE_TYPE exe_type) {return     COMPRESS_NONE;} // get compression used for embedding data of current app
   virtual Int           appEmbedCompressLevel              (                           EXE_TYPE exe_type) {return                 0;} // get compression used for embedding data of current app
   virtual DateTime      appEmbedSettingsTime               (                           EXE_TYPE exe_type) {return DateTime().zero();} // get settings time    for embedding data of current app
   virtual void          appSpecificFiles                   (MemPtr<PakFileData> files, EXE_TYPE exe_type) {                         } // get specific files      of current app
   virtual void          appLanguages                       (MemPtr<LANG_TYPE  > langs                   ) {langs.clear();           } // get supported languages of current app

   virtual Rect         menuRect    (                      ) {return D.rect();}
   virtual Rect       sourceRect    (                      ) {return D.rect();}
   virtual Str        sourceProjPath(C UID &id             ) {return S;}
   virtual ERROR_TYPE sourceDataLoad(C UID &id,   Str &data) {return EE_ERR_ELM_NOT_FOUND;}
   virtual Bool       sourceDataSave(C UID &id, C Str &data) {return false;}
   virtual void       sourceChanged (Bool activate=false) {} // called on change of current source

   virtual void publishSuccess(C Str &exe_name, EXE_TYPE exe_type, BUILD_MODE build_mode, C UID &project_id) {}

   virtual void validateActiveSources() {} // called when sources need to have their activation reset

   virtual Int  editorAddrPort(              ) {return     0;} // get Editor Network Interface Address Port
   virtual void editorAddr    (SockAddr &addr) {addr.clear();} // get Editor Network Interface Address

   virtual Bool elmValid    (C UID &id              ) {return false;} // if element of this ID exists in the project
   virtual Str  elmBaseName (C UID &id              ) {return     S;} // get base name of element
   virtual Str  elmFullName (C UID &id              ) {return     S;} // get full name of element
   virtual void elmHighlight(C UID &id, C Str  &name) {             } // highlight element
   virtual void elmOpen     (C UID &id              ) {             } // open      element
   virtual void elmLocate   (C UID &id              ) {             } // locate    element
   virtual void elmPreview  (C UID &id, C Vec2 &pos, Bool mouse, C Rect &clip) {} // draw element preview at 'pos' position, 'mouse'=if triggered by mouse

   virtual void focus() {}

   virtual Str idToText(C UID &id, Bool *valid=null) {if(valid)*valid=false; return S;} // return ID in text format (this can be element/object/waypoint/.. ID)

   struct ElmLink
   {
      UID      id;
      Str      full_name;
      ImagePtr icon;

      void set(C UID &id, C Str &full_name, C ImagePtr &icon) {T.id=id; T.full_name=full_name; T.icon=icon;}
   };
   virtual void getProjPublishElms(Memc<ElmLink> &elms) {} // get list of project elements for publishing
};
CChar8* ShortName(EXE_TYPE type);
} // namespace
/******************************************************************************/
