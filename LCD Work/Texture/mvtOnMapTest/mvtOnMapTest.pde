
int mSizeX = 16;
int mSizeY = 12;

int[][] map =  {{2 , 2, 2, 2, 2, 2, 1, 2, 2 , 2 , 0 , 2, 2, 2, 2, 2 },
                {2 , 0, 0, 0, 1, 2, 1, 0, 0 , 0 , 0 , 0, 0, 2, 2, 2 },
                {2 , 0, 0, 0, 1, 1, 1, 0, 0 , 0 , 0 , 0, 0, 0, 2, 2 },
                {2 , 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0, 0, 0, 0, 2 },
                {2 , 0, 0, 0, 0, 0, 0, 0, 0 , 1 , 0 , 1, 0, 0, 0, 2 },
                {2 , 0, 0, 0, 0, 1, 1, 0, 0 , 0 , 0 , 0, 0, 0, 0, 2 },
                {2 , 2, 2, 2, 2, 2, 1, 0, 0 , 0 , 0 , 0, 1, 0, 0, 0 },
                {2 , 0, 0, 0, 0, 0, 1, 0, 0 , 1 , 0 , 0, 0, 0, 0, 0 },
                {0 , 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0, 0, 1, 0, 0 },
                {2 , 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 1, 0, 0, 0, 2 },
                {2 , 0, 0, 1, 0, 0, 1, 0, 0 , 0 , 0 , 0, 0, 0, 0, 2 },
                {2 , 2, 2, 2, 2, 2, 2, 2, 0 , 0 , 0 , 2, 2, 2, 2, 2 }};

PImage[] tex = new PImage[3];

PVector p = new PVector(40, 40);
PVector pb = new PVector(40, 40);
boolean[] dir = {false, false, false, false};
boolean[] dirB = {false, false, false, false};

PImage[] player = new PImage[4];

void setup()
{
  size(480,360); //x1.5
  
  for(int i=0; i<3; i++)
  {
    tex[i] = loadImage("tex"+i+".png");
  }
  
  for(int i=0; i<4; i++)
  {
    player[i] = loadImage("tank"+i+".png");
  }
  
  for(int i=0; i<16; i++)
  {
    for(int j=0; j<12; j++)
    {
      image(tex[map[j][i]], 30*i, 30*j, 30, 30);
    }
  }
  
  frameRate(60);
}

void keyPressed()
{
  if (keyCode >= 37 && keyCode <= 40)
  {
    dir[keyCode-37] = true;
  }
  
  if (dir[1] || dir[3])
  {
    dir[0] = false;
    dir[2] = false;
  }
  println(dir[2]);
}

void keyReleased()
{
  if (keyCode >= 37 && keyCode <= 40)
  {
    dir[keyCode-37] = false;
  }
}

void move()
{
  if(dir[0] && map[floor((p.y+10)/30)][floor((pb.x-2)/30)] == 0)
  {
    p.x-=1.5;
  }
  if(dir[1] && map[floor((pb.y-2)/30)][floor((p.x+10)/30)] == 0)
  {
    p.y-=1.5;
  }
  if(dir[2] && map[floor((p.y+10)/30)][floor((p.x+22)/30)] == 0)
  {
    p.x+=1.5;
  }
  if(dir[3] && map[floor((p.y+22)/30)][floor((p.x+10)/30)] == 0)
  {
    p.y+=1.5;
  }
}

void draw()
{
  move();
  
  if (pb.x-2>=0 && pb.y-2>=0)
    image(tex[map[floor((pb.y-2)/30)][floor((pb.x-2)/30)]], 30*floor((pb.x-2)/30), 30*floor((pb.y-2)/30), 30, 30);
  if (pb.x-2>=0)
    image(tex[map[floor((pb.y+22)/30)][floor((pb.x-2)/30)]], 30*floor((pb.x-2)/30), 30*floor((pb.y+22)/30), 30, 30);
  if (pb.y-2>=0)
    image(tex[map[floor((pb.y-2)/30)][floor((pb.x+22)/30)]], 30*floor((pb.x+22)/30), 30*floor((pb.y-2)/30), 30, 30);
    
  image(tex[map[floor((pb.y+22)/30)][floor((pb.x+22)/30)]], 30*floor((pb.x+22)/30), 30*floor((pb.y+22)/30), 30, 30);
  
  //noStroke();
  //rect(p.x, p.y, 20, 20);
  if (dir[0] && !dir[2])
    image(player[3], p.x, p.y, 20, 20);
  if (!dir[0] && dir[1] && !dir[2] && !dir[3])
    image(player[0], p.x, p.y, 20, 20);
  if (!dir[0]&& dir[2])
    image(player[1], p.x, p.y, 20, 20);
  if (!dir[0] && !dir[1] && !dir[2] && dir[3])
    image(player[2], p.x, p.y, 20, 20);
  if (!dir[0] && !dir[1] && !dir[2] && !dir[3])
    image(player[1], p.x, p.y, 20, 20);
    
  pb = p;
}
