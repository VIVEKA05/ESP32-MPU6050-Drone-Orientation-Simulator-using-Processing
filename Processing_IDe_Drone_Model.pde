import processing.serial.*;

Serial port;

float pitch = 0;
float roll = 0;
float yaw = 0;

float spitch = 0;
float sroll  = 0;
float syaw   = 0;

float propSpin = 0;

void setup() {
  size(1100, 750, P3D);
  println(Serial.list());
  port = new Serial(this, "COM29", 115200); // change to your ESP32 COM port
  port.bufferUntil('\n');
}

void draw() {
  background(20);
  lights();
  directionalLight(255, 255, 255, -0.3, -1, -0.5);
  ambientLight(80, 80, 80);

  translate(width/2, height/2, 0);

  // Smooth filter
  spitch = lerp(spitch, pitch, 0.15);
  sroll  = lerp(sroll , roll , 0.15);
  syaw   = lerp(syaw  , yaw  , 0.15);

  // Rotate drone
  rotateY(radians(syaw));
  rotateX(radians(spitch));
  rotateZ(radians(sroll));

  drawDrone();
  propSpin += 0.6;
}

// ---------- DRAW DRONE ----------
void drawDrone() {
  // BODY
  pushMatrix();
  fill(70, 70, 75);
  box(140, 35, 140);
  popMatrix();

  // TOP COVER
  pushMatrix();
  translate(0, -20, 0);
  fill(200, 60, 60);
  box(90, 10, 90);
  popMatrix();

  // FRONT ARMS (RED)
  drawArm(120, 120, color(220, 40, 40));
  drawArm(-120, 120, color(220, 40, 40));

  // BACK ARMS (BLUE)
  drawArm(-120, -120, color(40, 120, 255));
  drawArm(120, -120, color(40, 120, 255));

  // LANDING LEGS
  drawLeg(80, 80);
  drawLeg(-80, 80);
  drawLeg(-80, -80);
  drawLeg(80, -80);

  // CAMERA
  pushMatrix();
  translate(0, 30, 90);
  fill(30);
  sphere(18);
  popMatrix();
}

// Draw drone arm
void drawArm(float x, float z, int c) {
  pushMatrix();
  translate(x/2, 0, z/2);
  rotateY(atan2(z, x));
  fill(c);
  box(170, 12, 12);
  popMatrix();
  drawMotor(x, z);
}

// Draw motor and propeller
void drawMotor(float x, float z) {
  pushMatrix();
  translate(x, 0, z);

  // MOTOR
  fill(30);
  cylinder(22, 20);

  // PROPELLER
  pushMatrix();
  translate(0, -10, 0);
  rotateY(propSpin);
  fill(220);
  box(120, 4, 14);
  box(14, 4, 120);
  popMatrix();

  popMatrix();
}

// Draw landing leg
void drawLeg(float x, float z) {
  pushMatrix();
  translate(x, 35, z);
  fill(180);
  box(8, 60, 8);
  translate(0, 30, 0);
  box(60, 8, 8);
  popMatrix();
}

// Cylinder function
void cylinder(float r, float h) {
  int sides = 24;
  beginShape(QUAD_STRIP);
  for(int i = 0; i <= sides; i++) {
    float angle = TWO_PI / sides * i;
    float x = cos(angle) * r;
    float z = sin(angle) * r;
    vertex(x, -h/2, z);
    vertex(x, h/2, z);
  }
  endShape();
}

// Serial reading
void serialEvent(Serial p) {
  String data = p.readStringUntil('\n');
  if(data != null) {
    data = trim(data);
    String[] val = split(data, ',');
    if(val.length == 3) {
      pitch = float(val[0]);
      roll  = float(val[1]);
      yaw   = float(val[2]);
    }
  }
}
