#ifndef __CAMERA_H_
#define __CAMERA_H_
#include <stdint.h>
#include <stdbool.h>



#define CAM_DEFAULT_I2C_ADDRESS       (0x32)
#pragma pack(1)
#define false 0
#define true 1
struct WonderCamQrCodeResultSumm {
  uint8_t current;
  uint8_t id;
  uint8_t __1[14];
  int16_t points[4][2];
  uint16_t len;
  uint8_t __2[14];
};

struct WonderCamFaceDetectResult {
  int16_t x;
  int16_t y;
  uint16_t w;
  uint16_t h;
} __attribute__((aligned(16)));

struct WonderCamObjDetectResult {
  int16_t x;
  int16_t y;
  uint16_t w;
  uint16_t h;
} __attribute__((aligned(16)));

struct WonderCamColorDetectResult {
  int16_t x;
  int16_t y;
  uint16_t w;
  uint16_t h;
} __attribute__((aligned(16)));

struct WonderCamLineResult {
  int16_t start_x;
  int16_t start_y;
  int16_t end_x;
  int16_t end_y;
  int16_t angle;
  int16_t offset;
} __attribute__((aligned(16)));
/************************************************************************************************
在读取标签数据后会返回这样一个结构体，其中x、y为小幻熊视觉模块上将标签标出的方框的
中心点XY坐标（以屏幕左上角为起点，向右为x轴正方向向下为y轴正方向），w、h为这个框的
宽度、高度，x_t、y_t、z_t对应的是标签在x、y、z三个方向上对应摄像头的偏移，x_r、y_r、z_r对应的
是标签在x、y、z三个方向上对应摄像头的旋转。
**************************************************************************************************/
struct WonderCamAprilTagResult {
  int16_t x;
  int16_t y;
  uint16_t w;
  uint16_t h;
  float x_t;
  float x_r;
  float y_t;
  float y_r;
  float z_t;
  float z_r;
} __attribute__((aligned(32)));

#pragma pack()



#define WONDERCAM_LED_ON           (true)
#define WONDERCAM_LED_OFF          (false)


typedef enum {
  APPLICATION_NONE = 0,
  APPLICATION_FACEDETECT,
  APPLICATION_OBJDETECT,
  APPLICATION_CLASSIFICATION,
  APPLICATION_FEATURELEARNING,
  APPLICATION_COLORDETECT,
  APPLICATION_LINEFOLLOW,
  APPLICATION_APRILTAG,
  APPLICATION_QRCODE,
  APPLICATION_BARCODE,
  APPLICATION_MAX,
} APPLICATION;

typedef enum {
  Aeroplane = 1,
  Bicycle,
  Bird,
  Boat,
  Bottle,
  Bus,
  Car,
  Cat,
  Chair,
  Cow,
  Diningtable,
  Dog,
  Horse,
  Motorbike,
  Person,
  Pottedplant,
  Sheep,
  Sofa,
  Train,
  Monitor
}Objects;


    void begin(void);
    bool firmwareVersion(char* str);
    bool hardwareVersion(char* str);
    bool protocalVersion(char* str);
    int currentFunc(void);
    bool changeFunc(uint8_t new_func);
    void setLed(bool new_state);
    bool updateResult(void);
    int readFromAddr(uint16_t addr,  uint8_t *buf, uint16_t leng);
    int writeToAddr(uint16_t addr, const uint8_t *buf, uint16_t leng);
    //
    // face detect
    bool anyFaceDetected(void);
    int numOfTotalFaceDetected(void);
    bool anyLearnedFaceDetected(void);
    int numOfTotalLearnedFaceDetected(void);
    bool anyUnlearnedFaceDetected(void);
    int numOfTotalUnlearnedFaceDetected(void);
    bool faceOfIdDetected(uint8_t id);
    bool getFaceOfId(uint8_t id, struct WonderCamFaceDetectResult *p);
    bool getFaceOfIndex(uint8_t index, struct WonderCamFaceDetectResult *p);
    //
    // obj detect
    bool anyObjDetected(void);
    int numOfObjDetected(void);
    bool objIdDetected(uint8_t id);
    int numOfObjIdDetected(uint8_t id);
    bool objDetected(uint8_t id, uint8_t index, struct WonderCamObjDetectResult *p);
    //
    //classification
    int classIdOfMaxProb(void);
    float classMaxProb(void);
    float classProbOfId(uint8_t id);
    //
    //Featuren Learning
    int featureIdOfMaxProb(void);
    float featureMaxProb(void);
    float featureProbOfId(uint8_t id);
    //
    //color detect
    bool anyColorDetected(void);
    int numOfColorDetected(void);
    bool colorIdDetected(uint8_t id);
    bool colorId(uint8_t id, struct WonderCamColorDetectResult *p);
    //
    //line follow
    bool anyLineDetected(void);
    int numOfLineDetected(void);
    bool lineIdDetected(uint8_t id);
    bool lineId(uint8_t id, struct WonderCamLineResult *p);
    //
    //AprilTag
    bool anyTagDetected(void);
    int numOfTotalTagDetected(void);
    bool tagIdDetected(uint16_t id);
    int numOfTagIdDetected(uint16_t id);
    bool tagId(uint16_t id, int index, struct WonderCamAprilTagResult *p);

    //
    //qrcode result
    bool qrCodeDetected(void);
    int qrCodeDataLength(void);
    int qrCodeData(uint8_t *buf);
    //
    //bar_code result
    bool barCodeDetected(void);
    int barCodeDataLength(void);
    int barCodeData(uint8_t *buf);
    //
    extern uint8_t current;
    extern uint8_t result_summ[128];



#endif
