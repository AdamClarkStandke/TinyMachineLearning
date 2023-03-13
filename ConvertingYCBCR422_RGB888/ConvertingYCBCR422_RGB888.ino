
// importing trained TFLITE model
#include "indoor_scene_recognition.h"

// importing TensorFlowLite library
#include <TensorFlowLite.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

//Start HERE God Damn it
#include "mbed.h"
#include <Arduino_OV767X.h>


#define PRESSED     0
#define BUTTON      p30

static mbed::DigitalIn  button(BUTTON);

int bytes_per_frame;
int bytes_per_pixel;

// re-sizing camera buffer to accommodate YCbCr422 format
uint8_t data[160 * 120 * 2];

template <typename T>
inline T clamp_0_255(T x) {
  return std::max(std::min(x, static_cast<T>(255)), static_cast<T>(0));
}

// converstion function
inline void ycbcr422_rgb888(int32_t Y, int32_t Cb, int32_t Cr, uint8_t* out) {
  Cr = Cr - 128;
  Cb = Cb - 128;

  out[0] = clamp_0_255((int)(Y + Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5)));
  out[1] = clamp_0_255((int)(Y - ((Cb >> 2) + (Cb >> 4) + (Cb >> 5)) - ((Cr >> 1) + (Cr >> 3) + (Cr >> 4)) + (Cr >> 5)));
  out[2] = clamp_0_255((int)(Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6)));
}

void setup() {
  Serial.begin(115600);
  while (!Serial);

  // initialize camera to capture QQVGA frames with YCbCr422 color format
  if (!Camera.begin(QQVGA, YUV422, 1)) {
    Serial.println("Failed to initialize camera!");
    while (1);
  }

  bytes_per_pixel = Camera.bytesPerPixel();
  bytes_per_frame = Camera.width() * Camera.height() * bytes_per_pixel;

  //Camera.testPattern();
}

void loop() {
  if(button == PRESSED) {
    Camera.readFrame(data);
    // buffer to store rgb888 images
    uint8_t rgb888[3];
    // sending the beginning of image transmission
    Serial.println("<image>");
    // sending width resolution
    Serial.println(Camera.width());
    // sending height resolution
    Serial.println(Camera.height());
    // sending out the pixel values in raster scan order
    for(int i = 0; i < bytes_per_frame; i+=bytes_per_pixel * 2) {
      // Note: U and V are swapped
    	const int32_t Y0 = data[i + 0];
    	const int32_t Cr = data[i + 1];
    	const int32_t Y1 = data[i + 2];
    	const int32_t Cb = data[i + 3];
      // convert to RGB888 from YCBCr422 color format
      ycbcr422_rgb888(Y0, Cb, Cr, &rgb888[0]);
      // outputting first pixel
      Serial.println(rgb888[0]);
      Serial.println(rgb888[1]);
      Serial.println(rgb888[2]);
      ycbcr422_rgb888(Y1, Cb, Cr, &rgb888[0]);
      // outputting second pixel
      Serial.println(rgb888[0]);
      Serial.println(rgb888[1]);
      Serial.println(rgb888[2]);
    }
    // sending the completion of image transmission for labeling 
    Serial.println("</image>");
  }
}
