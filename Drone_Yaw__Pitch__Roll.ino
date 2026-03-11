#include <Wire.h>
#include "MPU6050_6Axis_MotionApps20.h"

// MPU6050 object
MPU6050 mpu;

// INT pin
#define INTERRUPT_PIN 4

// DMP
bool dmpReady = false;
uint8_t mpuIntStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

// Quaternion and gravity
Quaternion q;
VectorFloat gravity;
float ypr[3];

// Calibration / offsets
#define GX_OFFSET 94
#define GY_OFFSET 171
#define GZ_OFFSET -185
#define AZ_OFFSET 1788  // optional accel offset if needed

// Interrupt flag
volatile bool mpuInterrupt = false;

// Store starting reference
float startYaw = 0, startPitch = 0, startRoll = 0;
bool referenceSet = false;

// Low-pass smoothing
float spitch = 0, sroll = 0, syaw = 0;

void IRAM_ATTR dmpDataReady() {
  mpuInterrupt = true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL

  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  // Apply offsets
  mpu.setXGyroOffset(GX_OFFSET);
  mpu.setYGyroOffset(GY_OFFSET);
  mpu.setZGyroOffset(GZ_OFFSET);
  mpu.setZAccelOffset(AZ_OFFSET);

  uint8_t devStatus = mpu.dmpInitialize();

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
    Serial.println("DMP Ready with INT");
  } else {
    Serial.print("DMP Initialization failed: ");
    Serial.println(devStatus);
  }
}

void loop() {
  if (!dmpReady) return;

  if (!mpuInterrupt && fifoCount < packetSize) return;
  mpuInterrupt = false;

  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();

  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
  } else if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;

    // Get orientation
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    float yaw = ypr[0] * 180/M_PI;
    float pitch = ypr[1] * 180/M_PI;
    float roll = ypr[2] * 180/M_PI;

    // Set reference starting orientation
    if (!referenceSet) {
      startYaw = yaw;
      startPitch = pitch;
      startRoll = roll;
      referenceSet = true;
    }

    // Relative orientation
    float relYaw = yaw - startYaw;
    float relPitch = pitch - startPitch;
    float relRoll = roll - startRoll;

    // Low-pass smoothing
    spitch = 0.9 * spitch + 0.1 * relPitch;
    sroll  = 0.9 * sroll  + 0.1 * relRoll;
    syaw   = 0.9 * syaw   + 0.1 * relYaw;

    // Send to Processing
    Serial.print(spitch); Serial.print(",");
    Serial.print(sroll); Serial.print(",");
    Serial.println(syaw);
  }
}
