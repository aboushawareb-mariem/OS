void CreateFile(char []);
void CopyFile(char [], char []);


main()
{
  while(1){
  char line2[100];
	char command[5];
	char View[4];
	char Execute[7];
	char buffer2[13312];
  char buffer[13312];
	char Delete[6];
	char Copy[4];
	char Create[6];
  char Dir[3];
  char CreateBuffer[512];
  char bufferee[512];

  char printBuffer[512];
  int counteree = 0;
  int CN =0;
  int z =0;
  int x = 0;
  int i = 0;
  int AsciiValue = 26;
  int ACounter =0;
  int Fourteen = 14;
  int endOfName=0;
  char FileNotFound[15];
  int FileNotFoundFlag = 0;
	char fileName[6];
  char fileName2[6];
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


   Copy[0] = 'c';
   Copy[1] = 'o';
   Copy[2] = 'p';
   Copy[3] = 'y';

   Create[0]='c';
   Create[1]='r';
   Create[2]='e';
   Create[3]='a';
   Create[4]='t';
   Create[5]='e';



	interrupt(0x21, 0, "SHELL>:\0", 0,0);
  for(i=0;i<100;i++)
    line2[i] = 0x0;
  i=0;
	interrupt(0x21, 1, line2, 0,0);
	//interrupt(0x21,0,line2,0,0);
  badCommand = 0;

  if(line2[0]==View[0]){
		for(i=1;i<4;i++){
			if(line2[i]!=View[i]){
				interrupt(0x21, 0, "Bad Command!\0", 0,0);
				badCommand=1;
				break;
			}
	}
    //interrupt(0x21,0, line2, 0 , 0);
  if(badCommand==0){
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
  //  for(ACounter=0;ACounter<13312;ACounter++){
  //     AsciiValue = (int)(buffer2[ACounter]);
  //    if(AsciiValue>126&&AsciiValue<255){
  //     for(Fourteen=0;Fourteen<14;Fourteen++)
  //         buffer2[Fourteen] = FileNotFound[Fourteen];
  //     for(Fourteen=14;Fourteen<13312;Fourteen++)
  //         buffer2[Fourteen] = 0;
  //       break;
   //
  //     }
  //     }

	    interrupt(0x21, 0, buffer2, 0, 0);
      for(i=0;i<13312;i++)
        buffer2[i] = 0x0;
      for(i=0;i<6;i++)
        fileName[i] = 0x0;

      i=0;
}
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
else if(line2[0]=='d')
{
  if(line2[1]!='i'){
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
}else{
  for(i=1;i<3;i++){
    if(line2[2]!='r')
    {
      interrupt(0x21, 0, "Bad Command!\0", 0,0);
      badCommand=1;
      break;
    }
   }
   if(badCommand==0)
   {
     for(x=0;x<160;x++){
         //interrupt(0x10,0xe*256+(x)+'0',0,0,0);
         printBuffer[x]=' ';
       } //
   //interrupt(0x21, 0, "BaaaHAHAHHAHA\0", 0,0);
   //interrupt(0x21, 0, "BaaaHAHAHHAHA\0", 0,0);
  interrupt(0x21, 2, bufferee,2,0);
//  interrupt(0x21, 3, 'messag',,0);
  CN = 0;
  counteree = 0;
  for(i=0;i<16;i++){
    //interrupt(0x21, 0, "0", 0,0);

  for(x=0;x<6;x++){
      if(bufferee[(i*32)+x]!='\0')
        printBuffer[counteree+x]=bufferee[(i*32)+x];

         }
        counteree+=6;
        for(z=6;z<32;z++){
          if(bufferee[(i*32)+z]!='\0'){
            CN++;
          }
        }
        if(bufferee[(i*32)]!='\0'){
        printBuffer[counteree] = ' ';
        counteree++;
        if(CN<10){
            printBuffer[counteree] = (CN + '0');
        }else{
            printBuffer[counteree] = (DIV(CN,10) + '0');
            counteree++;
            printBuffer[counteree] = (MOD(CN,10) + '0');

        }
        counteree++;
        printBuffer[counteree] = ' ';
        counteree++;
        }
        CN=0;

  }
  interrupt(0x21, 0, printBuffer, 0,0);
  //interrupt(0x21, 0, '\r', 0,0);  //interrupt(0x21, 0, '\r', 0,0);
   }
}
 }
 else if(line2[0]=='c'){
   if(line2[1]!='o'){
   for(i=1;i<6;i++){
     if(line2[i]!=Create[i])
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

      CreateFile(fileName);
    }
}else{
  for(i=1;i<4;i++){
  if(line2[i]!=Copy[i])
  {

    interrupt(0x21, 0, line2, 0,0);
    interrupt(0x21, 0, "Bad Command!\0", 0,0);
    badCommand=1;
    break;
  }
  }
  //interrupt(0x10,0xe*256+(badCommand)+'0',0,0,0);
  if(badCommand==0)
  {
   for(i=5;i<11;i++)
   {
       c=line2[i];
   if(c=='\0')
       break;
   fileName[x]=c;
   x++;
   }
  x=0;

  for(i=12;i<18;i++)
  {
     c=line2[i];
  if(c=='\0')
     break;
  fileName2[x]=c;
  x++;
  }
  x=0;

   CopyFile(fileName,fileName2);
  }
  }

 }


else
{
	interrupt(0x21, 0, "Bad Command!\0", 0,0);
	interrupt(0x21, 5,0, 0,0);
}
}
interrupt(0x21, 5,0, 0,0);
	while (1);
 // return 0;
}

void CopyFile(char File1[],char File2[]){
  char array[13312];
  int i=0;
  char c = '0';
  int sectNum = 1;
//  int mod = 0;
  for(i=0;i<13312;i++)
    array[i]=0x0;
  i=0;

  interrupt(0x21,3,File1,array,0);
  while(c!='\0'){
  //  interrupt(0x21,0,"gowa",0,0);
    c = array[i];
    i++;
    if(i == 512){
      sectNum++;
      i=0;
    }
  }
//  if(i > 0)
//  sectNum++;
  // interrupt(0x10,0xe*256+(sectNum)+'0',0,0,0);
//   mod=MOD(sectNum,512);
  // if(mod!=0)
  //   sectNum++;

  interrupt(0x21,8,File2,array,sectNum);

}
//
//
// void CreateFile(char fileName[]){
//
//       int charCntr=0;
//       int i =0;
//       int ii = 0;
//       int sectNum =0;
//       int mod=0;
//       char input[512];
//       char array[13312];
//       int boolean = 0;
//       char c = '0';
//
//       while(1)
//       {
//
// 	  interrupt(0x21, 0, "Please enter a line : \0", 0,0);
//     ii=0;
//      while(ii<512){
//        input[ii]=0;
//        ii++;
//      }
//       interrupt(0x21,1,input,0,0);
//
//
//
//         if(input[0] ==  0)
//         {
//
//             break;
//         }
//
//
//           // if(input[0]=='\0' || input[0] == '\0')
//           //    {
//           //     boolean = 1;
//            // interrupt(0x21, 0,input[0], 0,0);
//               // interrupt(0x10,0xe*256+input[0],0,0,0);
//           //     break;
//           //   }
    //
    //       while(c!='\0'){
    //         c = array[i];
    //         i++;
    //         if(i == 512)
    //         {sectNum++;
    //           i=0;
    //         }
    //       }
    //       if(i > 0)
    //       sectNum++;
    //     interrupt(0x10,0xe*256+(sectNum)+'0',0,0,0);
    //
    // interrupt(0x21,8,fileName,array,sectNum);
    // //interrupt(0x21,3,fileName,array,0);
    // //interrupt(0x21,0,array,0,0);
    //

//
// 	}
// }


void CreateFile(char fileName[]){

      int charCntr=0;
      int i =0;
      int ii = 0;
      int sectNum =0;
      int mod=0;
      char input[512];
      char array[13312];
      char array2[13312];
      int boolean = 0;

      while(1)
      {

	  interrupt(0x21, 0, "Please enter a line : \0", 0,0);
    ii=0;
     while(ii<512){
       input[ii]=0;
       ii++;
     }
      interrupt(0x21,1,input,0,0);



        if(input[0] ==  0)
        {

            break;
        }



        while(input[i]!='\0')
        {
        array[charCntr]=input[i];
        charCntr++;
        i++;
        if(i == 512)
        {i=0;
          sectNum++;
        }
        }
        if(i > 0)
        sectNum++;
        i=0;


    }

    interrupt(0x21,8,fileName,array,sectNum);

    // interrupt(0x21,3,fileName,array2,0);
    // interrupt(0x21,0,array2,0,0);



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
