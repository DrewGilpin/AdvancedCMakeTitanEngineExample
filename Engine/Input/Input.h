/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   Use 'Accelerometer' to access Accelerometer input.
   Use 'Gyroscope'     to access Gyroscope     input.
   Use 'Magnetometer'  to access Magnetometer  input.

   Use 'Location*' functions to access device world location.

/******************************************************************************/
#define        LongPressTime 0.55f // amount of time to consider any                   button press a long   press
#define      DoubleClickTime 0.25f // amount of time to consider Keyboard/Mouse/Joypad button press a double click
#define TouchDoubleClickTime 0.33f // amount of time to consider Touch                        press a double click
/******************************************************************************/
// ACCELEROMETER, GYROSCOPE, LOCATION
/******************************************************************************/
enum LOCATION_AUTHORIZATION_STATUS
{
   LAS_UNKNOWN   , // The user has not yet made a choice regarding whether this app can use location services
   LAS_RESTRICTED, // The app  cannot make use of Location because the device has this restricted (for example due to Parental Controls)
   LAS_DENIED    , // The user explicitly denied the use of location services for this app or location services are currently disabled in Settings.
   LAS_FOREGROUND, // The app  is authorized to make use of Location while running in foreground
   LAS_BACKGROUND, // The app  is authorized to make use of Location while running in foreground and background
};

C Vec& Accelerometer(); // get current value of the accelerometer             , if not supported then (0, 0, 0) is returned
C Vec& Gyroscope    (); // get current value of the gyroscope (radians/second), if not supported then (0, 0, 0) is returned
C Vec& Magnetometer (); // get current value of the magnetometer              , if not supported then (0, 0, 0) is returned

  Dbl       LocationLatitude (Bool gps=true); // get last known location latitude  (in degrees               ,    0 if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)
  Dbl       LocationLongitude(Bool gps=true); // get last known location longitude (in degrees               ,    0 if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)
  Flt       LocationAltitude (Bool gps=true); // get last known location altitude  (in meters above sea level,    0 if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)
  Flt       LocationAccuracy (Bool gps=true); // get last known location precision (in meters                ,    0 if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)
  Flt       LocationSpeed    (Bool gps=true); // get last known location speed     (in meters per second     ,    0 if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)
C DateTime& LocationTimeUTC  (Bool gps=true); // get last known location time      (in UTC time zone         , zero if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)

void LocationRefresh(Flt interval, Bool gps=true, Bool background=false); // after calling this function the device will start refreshing its location continuously each 'interval' seconds, 'gps'=if refresh the GPS (more precision) or Network (cell towers and internet access points), 'interval'=seconds between sequential updates (0..Inf) - small interval results in more frequent updates while big interval conserves the battery better. 'background'=if allow location updates even when the application is in background mode. This function can be called just once and the location will start refreshing itself as long as the app is active or until 'LocationDisable' is called. This and all other Location functions operate on GPS and Network separately, which means that you can start and stop refreshing both GPS and the Network independently.
void LocationDisable(              Bool gps=true                       ); // after calling this function the device will stop  refreshing its location                                     , 'gps'=if disable the GPS                  or Network

LOCATION_AUTHORIZATION_STATUS LocationAuthorizationStatus(); // get the current Location Authorization Status (this is used only on Apple platforms)

void MagnetometerRefresh(Flt interval=1.0f/30); // after calling this function the device will start refreshing direction of the magnetic field continuously each 'interval' seconds
void MagnetometerDisable(                    ); // after calling this function the device will stop  refreshing direction of the magnetic field
/******************************************************************************/
// VIRTUAL REALITY
/******************************************************************************/
struct VirtualReality // Virtual Reality - Head Mounted Display (HMD)
{
   Bool draw_2d; // if draw 2D layer on top of 3D (this includes manually drawn 2D graphics, UI and mouse cursor), if you don't use these, then disable this parameter for better performance, default=true

   // OpenVR SDK (usage of these methods requires linking to OpenVR SDK, increasing your executable file size and requiring the OpenVR DLL file to be present in the app folder)
   Bool OpenVRDetected()C; // if         OpenVR-compatible HMD is currently connected to the computer
   Bool OpenVRInit    () ; // initialize OpenVR-compatible HMD, this must be called in 'InitPre' if you want to use the device in your app, returns false if failed to initialize, true is returned if succeeded to initialize even if device is not currently connected

   // Oculus Rift SDK (usage of these methods requires linking to Oculus Rift SDK and increasing your executable file size)
   Bool OculusRiftDetected()C; // if         Oculus Rift is currently connected to the computer
   Bool OculusRiftInit    () ; // initialize Oculus Rift, this must be called in 'InitPre' if you want to use Oculus Rift in your app, returns false if failed to initialize, true is returned if succeeded to initialize even if device is not currently connected

   // Dummy
   void DummyInit(); // this will set the engine to think as if it was connected to a VR headset, which you can use for testing your app without a headset

   // get / set
   Bool    active      ()C;                     // if  HMD is currently connected to the computer and if one of the '*Init' methods were called with success
   CChar8* name        ()C {return _name     ;} // get HMD name
 C VecI2&  res         ()C {return _res      ;} // get HMD screen resolution
   Flt     eyeDistance ()C {return _eye_dist ;} // get HMD recommended eye distance as set in default profile
   Flt     refreshRate ()C {return _refresh  ;} // get HMD refresh rate
 C Vec2&   fov         ()C {return _fov      ;} // get HMD horizontal and vertical Field of View (in radians)
   Matrix  matrixCur   ()C;                     // get HMD pose at current moment                   , if not supported then 'MatrixIdentity' is returned
 C Matrix& matrix      ()C {return _matrix   ;} // get HMD pose at the start of current frame       , if not supported then 'MatrixIdentity' is returned
 C Matrix&  leftHand   ()C {return _left     ;} // get Left  Hand pose at the start of current frame, if not supported then 'MatrixIdentity' is returned
 C Matrix& rightHand   ()C {return _right    ;} // get Right Hand pose at the start of current frame, if not supported then 'MatrixIdentity' is returned
   Flt     pixelDensity()C {return _density  ;}   VirtualReality& pixelDensity(Flt density ); // get/set HMD rendering pixel density, 0..2, default=1
 C VecI2&  guiRes      ()C {return _gui_res  ;}   VirtualReality& guiRes      (Int w, Int h); // get/set HMD gui resolution, 1x1 .. Inf x Inf, default=1024x1024
   Flt     guiDepth    ()C {return _gui_depth;}   VirtualReality& guiDepth    (Flt depth   ); // get/set HMD gui depth (distance from camera in meters), 0..Inf, default=1, changing 'guiDepth' does not affect visible gui size
   Flt     guiSize     ()C {return _gui_size ;}   VirtualReality& guiSize     (Flt size    ); // get/set HMD gui size  (size when seen at 1 m distance), 0..Inf, default=1

   // operations
   void shut    (); // manually shut down HMD, normally you don't need to call this, as it will be called by the engine automatically
   void recenter(); // reset              HMD yaw orientation angle and position offset

private:
   Char8              _name[64];
   Flt                _eye_dist, _density, _refresh, _gui_depth, _gui_size, _left_eye_tex_aspect;
   Vec2               _fov;
   VecI2              _res, _gui_res;
   Rect               _left_eye_tex_rect;
   Matrix             _matrix, _left, _right;
   U64                _adapter_id;
   ImageRTC           _ui_ds;
   ImageRTPtr         _render, _ui;
   VirtualRealityApi *_api;

   VirtualReality();
   NO_COPY_CONSTRUCTOR(VirtualReality);
}extern
   VR;
/******************************************************************************/
// GENERAL INPUT
/******************************************************************************/
enum INPUT_TYPE : Byte // Input Device Type
{
   INPUT_NONE    , // None
   INPUT_KEYBOARD, // Keyboard
   INPUT_MOUSE   , // Mouse
   INPUT_JOYPAD  , // Joypad
};
struct Input
{
   Bool       pushed; // true=pushed, false=released
   INPUT_TYPE type  ; // input  type
   union
   {
      Byte          button; // for INPUT_MOUSE
      KB_KEY        key   ; // for INPUT_KEYBOARD
      JOYPAD_BUTTON jb    ; // for INPUT_JOYPAD
   };
   Byte device; // device index (for example Joypad device index, unused for Keyboard and Mouse)

   void set(Bool pushed, INPUT_TYPE type, Byte button, Byte device=0) {T.pushed=pushed; T.type=type; T.button=button; T.device=device;}
};
extern Memc<Input> Inputs; // all inputs that occurred in this frame (in order as they were received) 
/******************************************************************************/
struct TextEdit // Text Edit Settings
{
   Bool overwrite, // if cursor  is in overwriting mode
        password ; // if editing is in password mode from which you can't copy the text
   Int  cur      , // cursor    position
        sel      ; // selection position, -1=none

   void        reset() {overwrite=password=false; cur=0; sel=-1;}
   TextEdit() {reset();}
};
Bool EditText(Str &str, TextEdit &edit, Bool multi_line=false); // edit 'str' text according to keyboard input, returns true if text was changed
/******************************************************************************/
void DeviceVibrate(Flt intensity, Flt duration); // set device vibration, 'intensity'=how strong 0..1, 'duration'=how long (in seconds)
/******************************************************************************/
