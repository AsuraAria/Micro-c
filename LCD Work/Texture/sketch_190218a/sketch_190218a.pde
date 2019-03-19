void setup()
{
  //size(320,240);
  size(480,360);// x1.5
  PImage grass = loadImage("grass.png");
  
  image(grass, 0, 0, 30, 30);
  image(grass, 20, 0, 30, 30);
  image(grass, 0, 20, 30, 30);
  image(grass, 20, 20, 30, 30);
}
