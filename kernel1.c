void printString(char []);
void CreateFile(char []);
void readString(char []);
void printString2(char [], int);
void readFile(char*, char*);
void executeProgram(char*,int);
void terminate();
int DIV(int , int);
int MOD(int , int);
void readSector(char*, int);
void handleInterrupt21(int, int, int , int );
void deleteFile(char* );
void writeSector(char *, int );
void handleTimerInterrupt(int, int);

//char buffer[13312];
char line[90];
char mappy[512];
int processTableActive[8];
int processTableStackPointer[8];

// int processTableBusy[8];

// points to the process table entry currently executing
int currentProcess;

int TimerCounter = 0;

int main(){
int x = 0;
int i=0;
for(i=0;i<8;i++){
  setKernelDataSegment();
  processTableActive[i] = 0;
  restoreDataSegment();

  setKernelDataSegment();
  processTableStackPointer[i] = 0xFF00;
  restoreDataSegment();
  }
  setKernelDataSegment();
  currentProcess=0;
  restoreDataSegment();


  makeTimerInterrupt();
  makeInterrupt21();

  interrupt(0x21, 4, "shell\0", 0, 0);

//  interrupt(0x21, 4, "phello\0", 0, 0);
//   interrupt(0x21, 4, "hello2\0", 0, 0);

//   interrupt(0x21, 4, "hello1\0", 0, 0);

  //  for(x=0;x<8;x++){
  //       interrupt(0x10,0xe*256+(processTableActive[x])+'0',0,0,0);
  //  }
  //       //interrupt(0x10,0xe*256+(notFound)+'0',0,0,0);

//        printString(" MAIN \0");

  while(1);

}

void killProcess(int id){
    //interrupt(0x21, 0, "KILLED", 0, 0);
    setKernelDataSegment();
    processTableActive[id] = 0;
    restoreDataSegment();
}

 void handleTimerInterrupt(int segment, int sp){
   int i = 0;
   int nextProcess = -1;
   int nextSegment = 0;
   int found = 0;
   currentProcess = DIV(segment,0x1000)-2;
   interrupt(0x10,0xe*256+(currentProcess)+'0',0,0,0);
   //printString("Tic\0");
   setKernelDataSegment();
   processTableStackPointer[currentProcess] = sp;
   restoreDataSegment();
  if(TimerCounter == 100){
    // processTableActive[currentProcess] = 0;
    //printString(" Switch\0");
  for(i=1;i<8;i++){
      nextProcess = MOD(currentProcess+i,8);
    //  interrupt(0x10,0xe*256+(nextProcess)+'0',0,0,0);
        setKernelDataSegment();
      if(processTableActive[nextProcess] == 1){
        restoreDataSegment();
        setKernelDataSegment();
        currentProcess  = nextProcess;
        restoreDataSegment();


        found = 1;
        break;
      }
  }


//    interrupt(0x10,0xe*256+(currentProcess)+'0',0,0,0);


       setKernelDataSegment();

       TimerCounter = 0;
       restoreDataSegment();

  if(found==1){
    //  printString(" is 1\0");
    // nextSegment = (nextProcess+2)*0x1000;
    nextSegment = (currentProcess+2)*0x1000;
     returnFromTimer(nextSegment,processTableStackPointer[currentProcess]);
      // returnFromTimer(segment,sp);
  }else{
    //  printString("not 1\0");
    returnFromTimer(segment,sp);
  }

  } // close IF

    TimerCounter++;
    returnFromTimer(segment,sp);
  }// close method



void deleteFile(char* name){
  char directory[512];
  char mapy[512];
  int notFound = 1;
  int myNumber = 0;
  int i=0;
  int x = 0;
  int z = 0;
  int y = 0;

  readSector(directory,2);
  readSector(mapy,1);
  while(i<512&(notFound==1)){
      int j=0;

         while(j<6){
             if(name[j]=='\0')
                 break;

                 //check on the string match
             if(name[j]!=directory[i+j]){
                 notFound = 1;
                 break;
             }
             notFound = 0;
             myNumber = i;
             j+=1;
         }

         i+=32;
     }
     i=0;

        if(notFound==0){
            for(z=0;z<6;z++)
           directory[myNumber+z]=0x0;
         }

     if(notFound==1){
         printString("File not found DELETE!\n\r");
     }


                 z=6;
                 while(z<32){
                     x = myNumber+z;
                     if(directory[x]==0) break;
                     mapy[directory[x]]=0x0;
                     z++;
                    //   printString("removing from the mappp !\n\r");
                 }

    writeSector(mapy,1);
    writeSector(directory,2);

}


void writeSector(char* buffer, int sector)
{
    int AX=3*256+1;
    int track = DIV(sector,36);
    int CH = track;
    int relativeSectorNumber= (MOD (sector,18 ))+ 1;
    int CL = relativeSectorNumber;
    int headNumber=MOD(DIV(sector,18),2);
    int DH = headNumber;
    int DX=DH*256+0;
    int CX=CH*256+CL;
    interrupt(0x13,AX, buffer, CX, DX);

}

void writeFile(char* name,char* buffer,int sectors){
char dir[512];
char map[512];
int i=0;
int j=0;
int sectNum=0;
readSector(map,1);
readSector(dir,2);


while(i<16)
{
  if(dir[i*32]==0)
    break;
    i++;
}
if(i==16)
    printString("No Space\0");
else{
    //printString("There is space woohooo!");
for(j=0;j<32;j++)
{
    dir[i*32+j]=0x00;
}

for(j=0;j<6;j++)
{
    if(name[j]=="\0")
        break;
    dir[i*32+j]=name[j];
}
j=6;
for(sectNum=0;((sectNum<512) && (sectors > 0));sectNum++)
{
    if(map[sectNum]==0x00)
    {
        map[sectNum]=0xFF;
        dir[i*32+j]=sectNum;
        j++;
        writeSector(buffer,sectNum);
        buffer+= 512;
        sectors--;
    }
  }
}
writeSector(dir,2);
writeSector(map,1);

}

void executeProgram(char* name){
         char buffer[13312];
         int i = 0;
//--------------------------------------------------
         int segment = 0;

         for(i=0;i<8;i++){
           if(processTableActive[i]==0){
             segment = (i+2)*0x1000;
             //processTableBusy[i] = 1;
             setKernelDataSegment();
             processTableActive[i] = 1;
             restoreDataSegment();
             currentProcess = i;
             break;
           }
         }
//--------------------------------------------------
         readFile(name,buffer);
         //printString("am after readFile\0");
         for(i=0; i<13312; i++)
         {
             putInMemory(segment,i,buffer[i]);
     //counter++;
         }
         //printString("out");
         setKernelDataSegment();
        //  launchProgram(segment);
         initializeProgram(segment);
          restoreDataSegment();
        //  interrupt(0x21, 5, 0, 0, 0);
         //printString("afterLaunch");
}



void printString(char chars[]){
int i = 0;
char c;
int flag=1;
        while(flag==1)
    {

            c = *(chars+i);
            if(c=='\0'){
                //char chk=*(chars+i+1);
                flag=0;

                break;
                }
                i++;

                interrupt(0x10, 0xE*256+c, 0, 0, 0);
            }

}

void readString(char line[])
{

    int index = 0;
    char c = *(line+index) ;
    c = interrupt(0x16, 0, 0, 0, 0);

    while ( c != 0xd) //not equal enter
    {

        if( c == 0x8)
        {
            interrupt(0x10, 0xE*256+'\b', 0, 0, 0);
            index--;
            //printString2(line, index);
            interrupt(0x10, 0xE*256+' ', 0, 0, 0);
            interrupt(0x10, 0xE*256+'\b', 0, 0, 0);



        }else{

            *(line+index) = c;
            index++;
            interrupt(0x10, 0xE*256+c, 0, 0, 0);

        }

        c = interrupt(0x16, 0, 0, 0, 0);


    }

    if( c == 0xd){
        interrupt(0x10, 0xE*256+'\r', 0, 0, 0);

        interrupt(0x10, 0xE*256+0xa, 0, 0, 0);
        interrupt(0x10, 0xE*256+0x0, 0, 0, 0);
        interrupt(0x10, 0xE*256+'\b', 0, 0, 0);


       // printString2(line, index);
    }
}

void printString2(char arr[], int index)
{
    int i = 0;

// char c = *(arr+i);
// interrupt(0x10, 0xE*256+c, 0, 0, 0);

    while(i < index)
    {
        char c = *(arr+i);
        interrupt(0x10, 0xE*256+c, 0, 0, 0);
        i++;
    }
}


int DIV(int first, int second) // first / second
{
    int res = 0;
    while(first > 0)
    {
        first = first - second;
        res ++;
    }
    if(first<0){

        return res-1;
    }
    else{
        return res;
    }

}

int MOD(int first, int second)
{
    int dev = DIV(first, second);
    return (first -(second*dev));

}

void readSector(char* buffer, int sector)
{
    int AX=2*256+1;

    int track = DIV(sector,36);
    int CH = track;
    int relativeSectorNumber= (MOD (sector,18 ))+ 1;
    int CL = relativeSectorNumber;
    int headNumber=MOD(DIV(sector,18),2);
    int DH = headNumber;

    int DX=DH*256+0;

    int CX=CH*256+CL;

    interrupt(0x13,AX, buffer, CX, DX);


}

void handleInterrupt21(int ax, int bx, int cx, int dx)
{

    //printString("hello world");
    switch(ax)
    {
        case 0:

            printString(bx);
            break;


        case 1:

            readString(bx);
            break;

        case 2:

            readSector(bx,cx);
            break;

        case 3:

            //printString("ERROR");
           readFile(bx,cx);
            break;

            case 4:
            executeProgram(bx);
            break;


           case 5:
           terminate();
           break;

           case 6:
           writeSector(bx,cx);
           break;

           case 7:
           deleteFile(bx);
           break;

           case 8:
           writeFile(bx,cx,dx);
           break;

           case 9:
           killProcess(bx);
           break;
    }
}


void readFile(char* message, char* buffer){

     char directory[512];
     int notFound = 1;
     int myNumber = 0;
     int i=0;
     int x = 0;
     int g = 0;
     int bufferPointer = 0;
     int z = 0;
     int y = 0;
 //printString("readFile\0");
     readSector(directory,2);
     // printString("readSewctor\0");

     while(i<512&(notFound==1)){
         int j=0;

            while(j<6){
                if(message[j]=='\0'){
                    break;
                  }
                    notFound = 0;
                    //check on the string match
                if(message[j]!=directory[i+j]){
                    notFound = 1;
                    break;
                }
                myNumber = i;
                j+=1;
            }
            i+=32;
        }
        //interrupt(0x10,0xe*256+(myNumber-60)+'0',0,0,0);
        //interrupt(0x10,0xe*256+(notFound)+'0',0,0,0);
        if(notFound==0){
            bufferPointer = 0;
            z=6;
            while(z<32){
                //read each sector until i find a zero
                char tempBuffer[512];
                    x = myNumber+z;
                if(directory[x]==0) break;
                readSector(buffer+bufferPointer,directory[x]);
                //printString(tempBuffer);
                g=0;
                //copy the items from the tempbuffer to the buffer

                bufferPointer+=512;
                z++;
            }
          }

}


void terminate()
   {
    // char shell[5];
    // shell[0]='s';
    // shell[1]='h';
    // shell[2]='e';
    // shell[3]='l';
    // shell[4]='l';

    setKernelDataSegment();
    processTableActive[currentProcess] = 0;
    restoreDataSegment();
    //interrupt(0x21, 4, shell, 0x2000, 0);
   	while(1);

   }


            //printString(buffer);
