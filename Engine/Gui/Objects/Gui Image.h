/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************/
const_mem_addr struct GuiImage : GuiObj // Gui Image !! must be stored in constant memory address !!
{
   Bool       fit       ; // if maintain proportions of the image, default=false
   ALPHA_MODE alpha_mode; // alpha blending mode                 , default=ALPHA_BLEND
   Color      rect_color, // rectangle color                     , default=Gui.borderColor
              color     , // image     color                     , default=WHITE
              color_add ; // image     color add                 , default=TRANSPARENT
   ImagePtr   image     ; // image

   // manage
   virtual GuiImage& del   (                                        )override;                              // delete
           GuiImage& create(                  C ImagePtr &image=null);                                      // create
           GuiImage& create(C Rect     &rect, C ImagePtr &image=null) {create(image).rect(rect); return T;} // create
           GuiImage& create(C GuiImage &src                         );                                      // create from 'src'

   // set
   GuiImage& set(C ImagePtr &image); // set image

   // main
   virtual void draw(C GuiPC &gpc)override; // draw object

  ~GuiImage() {del();}
   GuiImage();

protected:
   virtual Bool save(File &f, CChar *path=null)C override;
   virtual Bool load(File &f, CChar *path=null)  override;
};
/******************************************************************************/
