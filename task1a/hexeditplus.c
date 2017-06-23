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
 	int fp=fopen(fileName, "rb");
 	if(fp==NULL){//cant open file
 		perror("Problem opening file specified\n");
 		return;
 	}
 	//get location and length input
 	char forRead[100];
 	int  location,length;

 	printf("Please enter <location> <length>\n");
 	fgets(forRead,100,stdin);
 	sscanf(forRead, "%x %d", &location, &length);
 		
 			fseek(fp,0,SEEK_END);
 	int fileSize=ftell(fp);
 	fseek(fp,0,SEEK_SET); 	 

 	if(location>fileSize){
 		perror("Illegal Values\n");
 		return;
	}
	if(debug){
		printf("Location: %#x\n",location);
		printf("Length: %d\n",length);
	}
	int finalSizeToRead=sizeof(unsigned char)*size*length;
	char* str; char c; int j=0;
	str=(char*)malloc(finalSizeToRead+1);
	fseek(fp, location, SEEK_SET);   // jump to beginning
	
	for(int i=0; i<finalSizeToRead; i++)
		fread(str+i,1,1,fp);
	fclose(fp);

	for(int i=0; i<finalSizeToRead; i++){
		if(i%2==0){
			c=str[i];
			str[i]=str[i+1];
			str[i+1]=c;
		}
	}
	printf("Read units(Hexadecimal): ");
	for(int i=0; i<finalSizeToRead; i++){
		int hexNUmber=(int)(*(unsigned char*)(&str[i]));
	     printf("%02x", hexNUmber);
	     if(i%2==1)
		 	printf(" ");
	}
	printf("\nRead units(Decimal): ");
	for(int i=0; i<finalSizeToRead; i=i+sizeof(unsigned char)*size){
			int number=0;
			if(i%sizeof(unsigned char)*size==0){
				int p=i;
				for(;p<(sizeof(unsigned char)*size)+i;p++)
					number=(number<<8)+((int)(*(unsigned char*)(&str[p])));
				printf("%d ",number);
			}
		
		}


		//int number= (((int)(*(unsigned char*)(&str[i])))<<8)+ (int)(*(unsigned char*)(&str[i+1]));

	
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
	fileName=strdup(data_pointer);
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
		

		printf("\n\n");
	}
	return 0;
}

