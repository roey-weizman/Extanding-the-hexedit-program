#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
	int debug=0;
	char* fileName=NULL;
	int size=1;
	char data_pointer[100]={0};

	char str[100];

typedef struct fun_desc {
 	char *name;
  	void (*fun)();
}fun_desc ;
// switching debugging mode
 void ToggleDebugMode() {
  if(!debug){
    debug=1;
    printf("Debug flag now on\n");
	}
  else{
  	debug=0;
  	printf("Debug flag now off\n");
  }
    
}

void FileDisplay() {
 
 	if(!fileName){//file is null
 		perror("There is no file to display\n");
 		return;
 	}
 	int fp;
 	if((fp=fopen(fileName, "r")<0)){//cant open file
 		perror("Problem opening file specified\n");
 		return;
 	}
 	//get location and length input
 	int count = 0;
 	char *LocLen;
 	printf("Please enter <location> <length>\n");
 	scanf("%s",&LocLen);
 	
 	//tokenizering
 	char *array[2];
	int i=0;

	array[i] = strtok(string," ");
	while(array[i]!=NULL&&i<2){
	   array[++i] = strtok(NULL," ");
	}
	int location=atoi(array[0]);
	int length= atoi(array[1]);
	if(debug){
		printf("Location: %#x\n",location);
		printf("Length: %d\n",length);
	}
	int decLocation=(int)strtol(location, NULL, 16);
	char* str;
	str=(char*)malloc(length*size);
	fseek(fp, decLocation, SEEK_SET);   // jump to beginning
	char ch;
	while(( ch = fgetc(fp))!= EOF || count < size*length){
 			 str[count++] = ch;
		}
	fclose(fp);
	printf("Read units(Hexadecimal): %x\n",str);
	printf("Read units(Decimal): %d\n",str);
	free(str);

}
// set size according to user input
void SetUnitSzie(){
	printf("Enter a Unit size:\n");
		int tmpSize; 
		tmpSize=(getc(stdin)-'0');	
	if(tmpSize!=1&&tmpSize!=2&&tmpSize!=4)
		perror("Not a valid value\n");
	else{
		size=tmpSize;
		if(debug)
			printf("Debug: set size to %d\n",size);
	}
			getc(stdin);

}
// set filename according to user input
void setFilename(){
	printf("Enter a file name:\n");
	gets(data_pointer);
	fileName=data_pointer;
	if(debug)
		printf("Debug: file name set to %s\n",fileName);
} 
char quit(){
	if(debug)
		printf("Quitting\n");
	exit(0);
}





int main(){
	
	 int bounds=5;
	struct fun_desc menu[] = { { "Toggle Debug Mode", &ToggleDebugMode },  { "Set File Name", &setFilename } ,{ "Set Unit Size", &SetUnitSzie },{ "File Display", &FileDisplay },{ "Quit", &quit },{ NULL, NULL } };	
	while(1){
		if(debug){
			printf("Unit size is: %d\n",size);
			printf("Filename is: %s\n",fileName);
			printf("Buffer address is: %#x\n\n",&data_pointer);
		}
		printf("Choose action:\n");
		for(int i=0;i<bounds;i++){
			printf("%d) %s\n",i,menu[i].name);
		}
		int n; 
		printf("Option: ");
		n=(getc(stdin)-'0');
		if(n>=0&&n<=bounds)
			printf("Within bounds\n\n");
		else {
			printf("Not within bounds\n");
			return -1;
		}
		getc(stdin);
		(menu[n].fun)();
		

		printf("DONE.\n\n");
	}
	return 0;
}
