void CreateFile(char[]);
int main()
{
  char line2[100];
	char command[5];
	char View[4];
	char Execute[7];
	char Delete[6];
	char Create[6];
	char buffer2[13312];
	int x = 0;
	int i = 0;
  int AsciiValue = 26;
  int ACounter =0;
  int Fourteen = 14;
  char FileNotFound[15];
  int FileNotFoundFlag = 0;
	char fileName[6];
	char c;
  int badCommand=0;
	View[0] = 'v';
	View[1] = 'i';
	View[2] = 'e';
	View[3] = 'w';

	Execute[0] = 'e';
	Execute[1] = 'x';
	Execute[2] = 'e';
	Execute[3] = 'c';
	Execute[4] = 'u';
	Execute[5] = 't';
	Execute[6] = 'e';

    FileNotFound[0] = 'F';
	FileNotFound[1] = 'I';
	FileNotFound[2] = 'L';
	FileNotFound[3] = 'E';
	FileNotFound[4] = ' ';
	FileNotFound[5] = 'N';
	FileNotFound[6] = 'O';
    FileNotFound[7] = 'T';
	FileNotFound[8] = ' ';
	FileNotFound[9] = 'F';
	FileNotFound[10] = 'O';
	FileNotFound[11] = 'U';
	FileNotFound[12] = 'N';
	FileNotFound[13] = 'D';
    

   Delete[0] ='d';
   Delete[1] ='e';
   Delete[2] ='l';
   Delete[3] ='e';
   Delete[4] ='t';
   Delete[5] ='e';
  
   Create[0]='c';
   Create[1]='r';
   Create[2]='e';
   Create[3]='a';
   Create[4]='t';
   Create[5]='e';

    
	interrupt(0x21, 0, "mariem\0", 0,0);
	interrupt(0x21, 0, "SHELL>:\0", 0,0);
	interrupt(0x21, 1, line2, 0,0);
	//interrupt(0x21,0,line2,0,0);

	if(line2[0]==View[0]){
		for(i=1;i<4;i++){
			if(line2[i]!=View[i]){
				interrupt(0x21, 0, "Bad Command!\0", 0,0);
				badCommand=1;
				break;
			}
	}
    //interrupt(0x21,0, line2, 0 , 0);
  if(badCommand==0)
	for(i=5;i<11;i++){
		c=line2[i];
		if(c=='\0')
			break;
		fileName[x]=c;
		x++;
	}
	 x=0;
   FileNotFoundFlag=0;
	 interrupt(0x21, 3, fileName, buffer2, 0); /*read the file into buffer*/
   for(ACounter=0;ACounter<13312;ACounter++){
      AsciiValue = (int)(buffer2[ACounter]);
     if(AsciiValue>126&&AsciiValue<255){
      for(Fourteen=0;Fourteen<14;Fourteen++)
          buffer2[Fourteen] = FileNotFound[Fourteen];
      for(Fourteen=14;Fourteen<13312;Fourteen++)
          buffer2[Fourteen] = 0;
        break;

      }
      }
  // }
  // if(FileNotFoundFlag==1){
//      interrupt(0x21, 0, FileNotFound, 0, 0);
  // }else{
	    interrupt(0x21, 0, buffer2, 0, 0);
// }
}
else if(line2[0]==Execute[0]){
	for(i=1;i<7;i++){
			if(line2[i]!=Execute[i]){
				interrupt(0x21, 0, "Bad Command!\0", 0,0);
				badCommand=1;
				break;
			}
	}
	if(badCommand==0)
	for(i=8;i<14;i++){
		c=line2[i];
		if(c=='\0')
			break;
		fileName[x]=c;
		x++;
	}
	x=0;

  for(ACounter=0;ACounter<13312;ACounter++){
     AsciiValue = (int)(buffer2[ACounter]);
    if(AsciiValue>126&&AsciiValue<255){
     for(Fourteen=0;Fourteen<14;Fourteen++)
         buffer2[Fourteen] = FileNotFound[Fourteen];
     for(Fourteen=14;Fourteen<13312;Fourteen++)
         buffer2[Fourteen] = 0;
       break;

     }
     }



	//interrupt(0x21, 4, "tstprg\0", 0x2000, 0);
	 interrupt(0x21, 4,fileName, 0x2000 , 0);
}
else if(line2[0]==Delete[0])
{
   for(i=1;i<6;i++)
		 {
			if(line2[i]!=Delete[i])
			{
				interrupt(0x21, 0, "Bad Command!\0", 0,0);
				badCommand=1;
				break;
			}
	     }
    if(badCommand==0)
    {
        for(i=7;i<13;i++)
	    {
		 c=line2[i];
		 if(c=='\0')
			break;
		  fileName[x]=c;
		  x++;
	    }
	   x=0;
      interrupt(0x21,7,fileName,0,0);
    }


}
else if(line2[0]==Create[0])
{

     interrupt(0x21, 0, "wohoo Command!\0", 0,0);	
  for(i=1;i<6;i++)
		 {
			if(line2[i]!=Create[i])
			{
				interrupt(0x21, 0, "Bad Command!\0", 0,0);
				badCommand=1;
				break;
			}
	     }
    if(badCommand==0)
    {
     interrupt(0x21, 0, "Not Command!\0", 0,0);	
        for(i=7;i<13;i++)
	    {
		 c=line2[i];
		 if(c=='\0')
			break;
		  fileName[x]=c;
		  x++;
	    }
	   x=0;
     CreateFile(fileName);
    }

}



else
{
	interrupt(0x21, 0, "Bad Command!\0", 0,0);
	interrupt(0x21, 5,0, 0,0);
}

interrupt(0x21, 5,0, 0,0);
	while (1);
 // return 0;
}

void CreateFile(char fileName[]){
	
      int charCntr=0;
      int i =0;
      int sectNum =0;
      char input[];
      char array[];
      while(1)
      { 
     
	  interrupt(0x21, 0, "PLease enter a line : \0", 0,0);
      interrupt(0x21,1,input,0,0);
          if(input=="")
          	break;
        while(input[i]!='\0')
        {

        charCntr++;
        i++;

        }

      } 
    fileName[charCntr+1]=" ";
    fileName[charCntr+2]=input;
    sectNum=charCntr/512;
    if(sectNum%512!=0)
    	sectNum++;
    interrupt(0x21,6,fileName,sectNum,0);

	}