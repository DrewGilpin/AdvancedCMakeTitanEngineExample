/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   Use 'SoundVolume' to set  volume for different sound groups
   Use 'SoundPlay'   to play custom sounds
   Use 'Sound'       to play custom sounds and control them later
   Use 'Listener'    to set  3D listener parameters which receives 3D sounds

/******************************************************************************/
enum VOLUME_GROUP : Byte // Sound Volume Group
{
   VOLUME_FX     , // Sound Effects
   VOLUME_MUSIC  , // Music
   VOLUME_AMBIENT, // Ambient Surroundings
   VOLUME_VOICE  , // Voices
   VOLUME_UI     , // User Interface
   VOLUME_NUM    , // number of volume groups
};
/******************************************************************************/
struct SoundVolumeClass
{
   void fx     (Flt v);   Flt fx     ()C {return _v[VOLUME_FX     ];} // set/get fx      volume (0..1)
   void music  (Flt v);   Flt music  ()C {return _v[VOLUME_MUSIC  ];} // set/get music   volume (0..1)
   void ambient(Flt v);   Flt ambient()C {return _v[VOLUME_AMBIENT];} // set/get ambient volume (0..1)
   void voice  (Flt v);   Flt voice  ()C {return _v[VOLUME_VOICE  ];} // set/get voice   volume (0..1)
   void ui     (Flt v);   Flt ui     ()C {return _v[VOLUME_UI     ];} // set/get UI      volume (0..1)
   void global (Flt v);   Flt global ()C {return _v[VOLUME_NUM    ];} // set/get global  volume (0..1)

private:
   Flt _v[VOLUME_NUM+1]; // +1 to make room for global

   SoundVolumeClass();
}extern
   SoundVolume; // Main Sound Volume Control
/******************************************************************************/
struct ListenerClass
{
   // get
 C Vec& pos  ()C {return _orn.pos    ;} // get listener position
 C Vec& dir  ()C {return _orn.dir    ;} // get listener forward direction
 C Vec& up   ()C {return _orn.perp   ;} // get listener up      direction
   Vec  right()C {return _orn.cross();} // get listener right   direction
 C Vec& vel  ()C {return _vel        ;} // get listener velocity

   // set
   ListenerClass& pos(C Vec &pos                        ); // set listener position
   ListenerClass& orn(C Vec &dir, C Vec &up=Vec(0, 1, 0)); // set listener orientation, 'dir'=forward direction (must be normalized), 'up'=up direction (must be normalized)
   ListenerClass& vel(C Vec &vel                        ); // set listener velocity

private:
   OrientP _orn;
   Vec     _vel;
   Int     _flag;

   ListenerClass();
}extern
   Listener; // Main 3D Sound Listener Control
/******************************************************************************/
enum FADE_CURVE : Byte
{
   FADE_LINEAR,
   FADE_SQRT  ,
   FADE_EQUAL_POWER=FADE_SQRT,
};
/******************************************************************************/
struct Sound
{
   // manage
   Sound& del   ();
   Sound& close (); // delete and wait until file handle is released, this method is slower than 'del', use it only if you need to modify the sound file
   Sound& create(               C Str         &name,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create             sound, 'name'=sound file name   ,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& create(               C UID         &id  ,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create             sound, 'id'  =sound file name ID,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& create(const_mem_addr SoundCallback &call,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create             sound, 'call'=sound call back   ,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& create(               C Str         &name, C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create          3D sound, 'name'=sound file name   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& create(               C UID         &id  , C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create          3D sound, 'id'  =sound file name ID, 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& create(const_mem_addr SoundCallback &call, C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create          3D sound, 'call'=sound call back   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& play  (               C Str         &name,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(name,             loop, volume, volume_group).play();} // create and play    sound, 'name'=sound file name   ,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& play  (               C UID         &id  ,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(id  ,             loop, volume, volume_group).play();} // create and play    sound, 'id'  =sound file name ID,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& play  (const_mem_addr SoundCallback &call,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(call,             loop, volume, volume_group).play();} // create and play    sound, 'call'=sound call back   ,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& play  (               C Str         &name, C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(name, pos, range, loop, volume, volume_group).play();} // create and play 3D sound, 'name'=sound file name   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& play  (               C UID         &id  , C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(id  , pos, range, loop, volume, volume_group).play();} // create and play 3D sound, 'id'  =sound file name ID, 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& play  (const_mem_addr SoundCallback &call, C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(call, pos, range, loop, volume, volume_group).play();} // create and play 3D sound, 'call'=sound call back   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)

   // stop / play
   Sound& stop (); // stop
   Sound& pause(); // pause
   Sound& play (); // play

   // get / set
                                   Bool is       ()C; // if created
                                   Bool playing  ()C; // if playing
                            SOUND_CODEC codec    ()C; //     get source codec
                                CChar8* codecName()C; //     get source codec name
                                 C Str& name     ()C; //     get source file  name
                                   UID  id       ()C; //     get source file  name ID
                                   Long size     ()C; //     get source raw   size   in bytes
                                   Flt  length   ()C; //     get source time  length in seconds
                                   Long samples  ()C; //     get source number of samples
                                   Int  channels ()C; //     get source number of channels
                                   Int  frequency()C; //     get source frequency
                                   Int  bitRate  ()C; //     get source bit rate
                                   Flt  timeLeft ()C; //     get sound remaining time     , 0..length (), "length()-time()"
   Sound& raw   (  Long raw   );   Long raw      ()C; // set/get sound raw      position  , 0..size   ()
   Sound& sample(  Long sample);   Long sample   ()C; // set/get sound sample   position  , 0..samples()
   Sound& time  (  Flt  t     );   Flt  time     ()C; // set/get sound time     position  , 0..length ()
   Sound& frac  (  Flt  f     );   Flt  frac     ()C; // set/get sound fraction position  , 0..1
   Sound& loop  (  Bool loop  );   Bool loop     ()C; // set/get sound looping            , true/false
   Sound& volume(  Flt  volume);   Flt  volume   ()C; // set/get sound volume             , 0..1
   Sound& speed (  Flt  speed );   Flt  speed    ()C; // set/get sound speed              , 0..3, default=1
   Sound& range (  Flt  range );   Flt  range    ()C; // set/get sound 3D range multiplier, 0..Inf
   Sound& pos   (C Vec &pos   ); C Vec& pos      ()C; // set/get sound 3D position
   Sound& vel   (C Vec &vel   ); C Vec& vel      ()C; // set/get sound 3D velocity

   // volume fade
                                                  Flt        fade     ()C; //     get current fade value
   Sound& fadeCurve        (FADE_CURVE curve );   FADE_CURVE fadeCurve()C; // set/get fade curve
   Sound& fadeInFromSilence(Flt fade_duration);                            // perform volume fade-in  from silence              to max  volume
   Sound& fadeIn           (Flt fade_duration);                            // perform volume fade-in  from current volume level to max  volume
   Sound& fadeOut          (Flt fade_duration);                            // perform volume fade-out from current volume level to zero volume

   // data callback
   Sound& callback(SoundDataCallback *callback);   SoundDataCallback* callback()C; // set/get data callback, it will be called every time a new portion of data is processed by the sound

   // io
   Bool save(File &f, CChar *path=null)C; // 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail
   Bool load(File &f, CChar *path=null) ; // 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

           ~Sound() {del();}
            Sound() {sound=null;}
            Sound(C Sound &src);
   void operator=(C Sound &src);

private:
   Ptr sound;
};
/******************************************************************************/
void SoundPlay(               C Str         &name,                          Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play    sound, 'name'=sound file name                                                                           , 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
void SoundPlay(               C UID         &id  ,                          Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play    sound, 'id'  =sound file name ID                                                                        , 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
void SoundPlay(const_mem_addr SoundCallback &call,                          Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play    sound, 'call'=sound call back                                                                           , 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
void SoundPlay(               C Str         &name, C Vec &pos, Flt range=1, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play 3D sound, 'name'=sound file name   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
void SoundPlay(               C UID         &id  , C Vec &pos, Flt range=1, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play 3D sound, 'id'  =sound file name ID, 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
void SoundPlay(const_mem_addr SoundCallback &call, C Vec &pos, Flt range=1, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play 3D sound, 'call'=sound call back   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)

Flt SoundMinVolume    ();   void SoundMinVolume    (Flt volume); // get/set minimum volume required to play a sound            , default=0.02, if volume of a sound is less than the specified value then it will be skipped for faster processing
Int SoundMaxConcurrent();   void SoundMaxConcurrent(Int max   ); // get/set maximum number of concurrent sounds                , default=16  , if number of sounds exceeds the specified limit then sounds with lower priority will be skipped for faster processing, specifying negative value (-1) is the same as allowing unlimited number of concurrent sounds
Int SoundMaxThreads   ();   void SoundMaxThreads   (Int max   ); // get/set maximum number of threads used for sound processing, default=1
/******************************************************************************/
