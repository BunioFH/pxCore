// pxCore CopyRight 2007-2015 John Robinson
// pxImage9.h

#ifndef PX_IMAGE9_H
#define PX_IMAGE9_H

#include "pxOffscreen.h"
//#include "pxTextureCacheObject.h"
#include "pxResource.h"

class pxImage9: public pxObject, pxResourceListener {
public:
  rtDeclareObject(pxImage9, pxObject);
  rtProperty(url, url, setUrl, rtString);
  rtProperty(insetLeft, insetLeft, setInsetLeft, float);
  rtProperty(insetTop, insetTop, setInsetTop, float);
  rtProperty(insetRight, insetRight, setInsetRight, float);
  rtProperty(insetBottom, insetBottom, setInsetBottom, float);
  rtProperty(sourceLeft, sourceLeft, setSourceLeft, float);
  rtProperty(sourceTop, sourceTop, setSourceTop, float);
  rtProperty(sourceRight, sourceRight, setSourceRight, float);
  rtProperty(sourceBottom, sourceBottom, setSourceBottom, float);
  rtProperty(resource, resource, setResource, rtObjectRef);

  pxImage9(pxScene2d* scene) : pxObject(scene),mInsetLeft(0),mInsetTop(0),mInsetRight(0),mInsetBottom(0),
                               mSourceLeft(0),mSourceTop(0),mSourceRight(0),mSourceBottom(0),imageLoaded(false)
  {
    mResource = pxImageManager::getImage("");
    mw = -1;
    mh = -1;
  }
  
  rtError url(rtString& s) const;
  rtError setUrl(const char* s);

  rtError resource(rtObjectRef& o) const { /*rtLogDebug("!!!!!!!!!!!!!!!!!!!!pxImage9 getResource\n");*/o = mResource; return RT_OK; }
  rtError setResource(rtObjectRef o) { /*rtLogDebug("!!!!!!!!!!!!!!!!!!!!!!!pxImage9 setResource\n");*/mResource = o; return RT_OK; }
    
  rtError insetLeft(float& v) const { v = mInsetLeft; return RT_OK; }
  rtError setInsetLeft(float v) { mInsetLeft = v; return RT_OK; }
  rtError insetTop(float& v) const { v = mInsetTop; return RT_OK; }
  rtError setInsetTop(float v) { mInsetTop = v; return RT_OK; }
  rtError insetRight(float& v) const { v = mInsetRight; return RT_OK; }
  rtError setInsetRight(float v) { mInsetRight = v; return RT_OK; }
  rtError insetBottom(float& v) const { v = mInsetBottom; return RT_OK; }
  rtError setInsetBottom(float v) { mInsetBottom = v; return RT_OK; }

  rtError sourceLeft(float& v) const { v = mSourceLeft; return RT_OK; }
  rtError setSourceLeft(float v) { mSourceLeft = v; return RT_OK; }
  rtError sourceTop(float& v) const { v = mSourceTop; return RT_OK; }
  rtError setSourceTop(float v) { mSourceTop = v; return RT_OK; }
  rtError sourceRight(float& v) const { v = mSourceRight; return RT_OK; }
  rtError setSourceRight(float v) { mSourceRight = v; return RT_OK; }
  rtError sourceBottom(float& v) const { v = mSourceBottom; return RT_OK; }
  rtError setSourceBottom(float v) { mSourceBottom = v; return RT_OK; }

  virtual ~pxImage9();
  virtual void onInit();
  virtual void resourceReady(rtString readyResolution);
  //virtual bool onTextureReady(pxTextureCacheObject* textureCacheObject) {return true;}
  virtual void sendPromise();
  virtual void createNewPromise() { rtLogDebug("pxImage9 ignoring createNewPromise\n"); }
  virtual float getOnscreenWidth();
  virtual float getOnscreenHeight();
  
protected:
  virtual void draw();
  void loadImage(rtString Url);
  inline rtImageResource* getImageResource() const { return (rtImageResource*)mResource.getPtr(); }
  
  float mInsetLeft, mInsetTop, mInsetRight, mInsetBottom;
  float mSourceLeft, mSourceTop, mSourceRight, mSourceBottom;
  rtObjectRef mResource;

  bool imageLoaded;
  bool mListenerAdded;
};

#endif
