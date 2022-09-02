/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   Use 'Keyboard' to access Keyboard input.

   Use 'KbSc' to describe keyboard shortcuts.

/******************************************************************************/
struct KeyboardKey
{
   Char   c;
   KB_KEY k;
   Byte   flags;

   Bool any    ()C {return    c || k              ;} // if any character or key pressed
   Bool ctrl   ()C {return    FlagOn(flags, CTRL );} // if any  Control pressed
   Bool shift  ()C {return    FlagOn(flags, SHIFT);} // if any  Shift   pressed
   Bool alt    ()C {return    FlagOn(flags, ALT  );} // if any  Alt     pressed
   Bool win    ()C {return    FlagOn(flags, WIN  );} // if any  Win     pressed
   Bool lalt   ()C {return    FlagOn(flags, LALT );} // if Left Alt     pressed
   Bool first  ()C {return    FlagOn(flags, FIRST);} // if this is the first press of the key (if false then it's a repeated press)
   Bool ctrlCmd()C {return APPLE ? win () : ctrl();} // if any Ctrl is on (on platforms other than Apple), and if any Command is on (on Apple platforms)
   Bool winCtrl()C {return APPLE ? ctrl() : win ();} // if any Win  is on (on platforms other than Apple), and if any Control is on (on Apple platforms)

   Bool operator()(Char   c)C {return T.c==c;} // use simple == instead of 'EqualCS' for performance reasons
   Bool operator()(Char8  c)C {return T.c==c;} // use simple == instead of 'EqualCS' for performance reasons
   Bool operator()(KB_KEY k)C {return T.k==k;}
   Bool first     (KB_KEY k)C {return T.k==k && first();} // if this is the first press of 'k' key

   void clear() {c='\0'; k=KB_NONE; flags=0;}

   void eat()C; // eat this key input from this frame so it will not be processed by the remaining codes in frame

   enum
   {
      CTRL =1<<0,
      SHIFT=1<<1,
      ALT  =1<<2,
      WIN  =1<<3,
      LALT =1<<4,
      FIRST=1<<5,
   };
};
struct KeyboardClass // Keyboard Input
{
   // get
   const KeyboardKey k; // key pressed in this frame
   Bool kf(KB_KEY k)C {return T.k.first(k);} // if key 'k' is pressed and it's the first press

   Bool b (KB_KEY k)C {return ButtonOn(_button[k]);} // if key 'k' is on
   Bool bp(KB_KEY k)C {return ButtonPd(_button[k]);} // if key 'k' pushed   in this frame
   Bool br(KB_KEY k)C {return ButtonRs(_button[k]);} // if key 'k' released in this frame
   Bool bd(KB_KEY k)C {return ButtonDb(_button[k]);} // if key 'k' double clicked

   Bool ctrl ()C {return _ctrl ;} // if any Ctrl  is on (this is equal to "b(KB_LCTRL ) || b(KB_RCTRL )")
   Bool shift()C {return _shift;} // if any Shift is on (this is equal to "b(KB_LSHIFT) || b(KB_RSHIFT)")
   Bool alt  ()C {return _alt  ;} // if any Alt   is on (this is equal to "b(KB_LALT  ) || b(KB_RALT  )")
   Bool win  ()C {return _win  ;} // if any Win   is on (this is equal to "b(KB_LWIN  ) || b(KB_RWIN  )")

   Char   keyChar  (KB_KEY key)C; // get key character, example: keyChar  (KB_SPACE) -> ' '    , keyChar  (KB_UP) -> '\0'
  CChar8* keyName  (KB_KEY key)C; // get key name     , example: keyName  (KB_SPACE) -> "Space", keyName  (KB_UP) -> "Up"
  CChar * keySymbol(KB_KEY key)C; // get key symbol   , example: keySymbol(KB_SPACE) -> "Space", keySymbol(KB_UP) -> "⯅", Warning: this function might return "⯇⯈⯆⯅", if you want to display symbols on the screen be sure to include these characters in your Font

   Bool hardware(          )C {return _hardware;} // if hardware keyboard is available
   Bool rect    (Rect &rect)C;                    // get on-screen keyboard rectangle, false if no on-screen keyboard is currently displayed

   KB_KEY qwerty(KB_KEY qwerty)C; // convert key from QWERTY layout to layout of current keyboard

   // operations
   void eat(          ); // eat all    input from this frame so it will not be processed by the remaining codes in frame, this disables all BS_FLAG states (BS_PUSHED, BS_RELEASED, etc.) except BS_ON
   void eat(Char   c  ); // eat 'c'    input from this frame so it will not be processed by the remaining codes in frame, this disables all BS_FLAG states (BS_PUSHED, BS_RELEASED, etc.) except BS_ON
   void eat(Char8  c  ); // eat 'c'    input from this frame so it will not be processed by the remaining codes in frame, this disables all BS_FLAG states (BS_PUSHED, BS_RELEASED, etc.) except BS_ON
   void eat(KB_KEY key); // eat 'key'  input from this frame so it will not be processed by the remaining codes in frame, this disables all BS_FLAG states (BS_PUSHED, BS_RELEASED, etc.) except BS_ON
   void eatKey(       ); // eat 'Kb.k' input from this frame so it will not be processed by the remaining codes in frame, this disables all BS_FLAG states (BS_PUSHED, BS_RELEASED, etc.) except BS_ON

   void nextKey(); // specify that you've processed 'Kb.k' and would like to proceed to the next key in the queue

   void queue(C KeyboardKey &key); // manually add 'key' to the buffer to be processed later

   Bool exclusive()C {return _exclusive;}   void exclusive(Bool on); // get/set keyboard exclusive mode (which disables Windows key on Windows platform), default=false

   // IMM (Windows Input Method Manager) control
   Bool       immNative   ()C;   void immNative(Bool native); // get/set if native typing mode is currently enabled
   Int        immCursor   ()C {return _imm_cursor   ;}        // get     IMM cursor position
 C VecI2    & immSelection()C {return _imm_selection;}        // get     IMM clause selection range, where x=min index, y=max index
 C Str      & immBuffer   ()C {return _imm_buffer   ;}        // get     IMM text buffer
 C Memc<Str>& immCandidate()C {return _imm_candidate;}        // get     IMM candidate list

   Bool    ctrlCmd    ()C {return APPLE ? _win  : _ctrl ;} // if any Ctrl is on (on platforms other than Apple), and if any Command is on (on Apple platforms)
   Bool    winCtrl    ()C {return APPLE ? _ctrl : _win  ;} // if any Win  is on (on platforms other than Apple), and if any Control is on (on Apple platforms)
   CChar8* ctrlCmdName()C {return APPLE ? "Cmd" : "Ctrl";}
   CChar8* winCtrlName()C {return APPLE ? "Ctrl": "Win" ;}

private:
   Bool        _ctrl, _shift, _alt, _win, _cur_hidden, _swap_ctrl_cmd, _visible, _imm, _imm_candidate_hidden, _exclusive, _hardware;
   Byte        _key_buffer_pos, _key_buffer_len;
   BS_FLAG     _button[256];
   Char8       _key_char[256];
   KeyboardKey _key_buffer[256];
   KB_KEY      _qwerty[256];
   Int         _cur, _last, _imm_cursor, _last_key_scan_code;
   Flt         _curh_t, _curh_tn;
   Dbl         _last_t;
   RectI       _recti;
   VecI2       _imm_selection;
   Str         _imm_buffer;
   Memc<Str>   _imm_candidate, _imm_candidate_temp;
   CChar8     *_key_name  [256];
   CChar      *_key_symbol[256];
#if WINDOWS_OLD
   Ptr         _device;
   Ptr         _imc;
#endif

	KeyboardClass();
   NO_COPY_CONSTRUCTOR(KeyboardClass);
}extern
   Kb;
inline KeyboardClass &Keyboard=Kb; // 'Keyboard' alias ('Keyboard' can be used the same way as 'Kb')
/******************************************************************************/
enum KBSC_FLAG // Keyboard Shortcut Flags
{
   KBSC_CTRL =0x01, // Control required
   KBSC_SHIFT=0x02, // Shift   required (this is ignored for KBSC_CHAR, instead please specify upper/lower case of the character)
   KBSC_ALT  =0x04, // Alt     required (for KBSC_CHAR - only left alt is checked, also for KBSC_CHAR this may not work well if KBSC_CTRL is enabled too, as on Windows pressing Ctrl+Alt triggers accented characters and regular characters may not get generated)
   KBSC_WIN  =0x08, // Win     required

   KBSC_CTRL_CMD=0x10, // Control required on non-Apple platforms, and Command required on Apple platforms
   KBSC_WIN_CTRL=0x20, // Win     required on non-Apple platforms, and Control required on Apple platforms

   KBSC_REPEAT=0x40, // allow repeated execution when holding key for a long time (currently this affects only KBSC_KEY, as KBSC_CHAR always allow this)
};
enum KBSC_MODE : Byte // Keyboard Shortcut Mode
{
   KBSC_NONE, // disabled
   KBSC_CHAR, // treat 'index' as Char
   KBSC_KEY , // treat 'index' as KB_KEY
};
struct KbSc // Keyboard Shortcut
{
   Byte      flag ; // KBSC_FLAG
   KBSC_MODE mode ; // mode
   UShort    index; // Char/KB_KEY depending on 'mode'

   // get
   Bool is    ()C {return mode!=KBSC_NONE;} // if shortcut is valid
   Bool pd    ()C; // if pushed in this frame
   Str  asText()C; // get text describing the shortcut

   // operations
   void eat()C; // eat this shortcut keys input from this frame so it will not be processed by the remaining codes in frame

   KbSc(                       ) {T.index=0           ; T.flag=0   ; T.mode=KBSC_NONE;}
   KbSc(Char8  c  , Byte flag=0) {T.index=Char8To16(c); T.flag=flag; T.mode=KBSC_CHAR;}
   KbSc(Char   c  , Byte flag=0) {T.index=c           ; T.flag=flag; T.mode=KBSC_CHAR;}
   KbSc(KB_KEY key, Byte flag=0) {T.index=key         ; T.flag=flag; T.mode=KBSC_KEY ;}
};
/******************************************************************************/
