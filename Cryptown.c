#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int choice; //menu var
void Caesar(); //Encrypts the message
void Affine();
void Permutation();

int main() {
    printf("---------- Welcome to Cryptown -----------\n");
    do{
        printf("Choose one of the encryption algorithms below:\n\n");
        printf("1. Caesar\n2. Vigenere\n3. Affine\n4. HILL\n5. Permutation\n6. Vernam Cipher (OTP)\n");
        printf("Choose from 1-6:\t ");
        //printf("\n\n-------------- Made by fkaroli ---------------\n");
        scanf("%d",&choice);
        
    } while (choice<1 || choice>6);
    switch (choice)
    {
    case 1:
        printf("---------------- Caesar Cypher ---------------\n");
        Caesar();
        break;
    case 2:
        //Vigenere();
        break;
    case 3:
        printf("---------------- Affine Cypher ---------------\n");
        Affine();
        
        break;
    case 4:
        //Hill();
        break;
    case 5:
        printf("---------------- Permutation Cypher ---------------\n");
        Permutation();
        break;
    case 6:
        printf("---------------- Vernam Cypher (OTP) ---------------\n");
        //OTP();
        break;
    default:
        printf("Some error occured!\n");
        break;
    }
    
    return 0;
}

/*---------------------- CAESAR ----------------------*/

void Caesar(){
    char message[100];
    int i,ch,key,cho;
    printf("Whould you like to Encrypt or Decrypt the message?\n1.Encryption\n2.Decryption\n");
    scanf("%d",&cho);

    /* I use the below to handle the ENTER from the menu
    because the new line is still on the buffer
    causing an error to my next gets() */
    gets(message);

    switch(cho){
        case 1:
            printf("Enter the message to encrypt: \n");
            //scanf("%s",message);
            gets(message);

            printf("Enter the key:\n");
            scanf("%d",&key);

            for(i=0;message[i]!='\0';i++){  //While message[i] is not a zero character
                ch=message[i];  //ch takes i character of the word

                if(ch>='a' && ch<='z'){ //if character is somewhere between 'a' and 'z'
                    ch=ch+(key%26); //Encryption key is added mod 26 (26 characters in the English Language)
                    if(ch>'z'){ //If ch is bigger than 'z' we substruct 'z' and then start back from 'a' character
                        ch=ch-'z'+'a'-1;
                    }
                    message[i]=ch;
                }else if(ch>='A' && ch<='Z'){   //if character is somewhere between 'A' and 'Z'
                    ch=ch+(key%26); //Encryption key is added mod 26 (26 characters in the English Language)
                    if(ch>'Z'){ //If ch is bigger than 'Z' we substruct 'Z' and then start back from 'A' character
                        ch=ch-'Z'+'A'-1;
                    }   
                    message[i]=ch;
                }
            }
            printf("Encryped message is : %s\n",message);
            break;
        case 2:
            printf("Enter the encrypted message: \n");
            //scanf("%s",message);
            gets(message);

            printf("Enter Key: \n");
            scanf("%d",&key);

            for(i=0;message[i]!='\0';++i){  //While message[i] is not a zero character
                ch=message[i];  //ch takes i character of the word

                if(ch>='a' && ch<='z'){ //if character is somewhere between 'a' and 'z'
                    ch=ch-(key%26); //Encryption key is substructed mod 26 (26 characters in the English Language)
                    if(ch<'a'){ //If ch is lower than 'a' we add 'z' and then substruct a + 1
                        ch=ch+'z'-'a'+1;
                    }
                    message[i]=ch;
                }else if(ch>='A' && ch<='Z'){   //if character is somewhere between 'A' and 'Z'
                    ch=ch-(key%26); //Encryption key is substructed mod 26 (26 characters in the English Language)
                    if(ch <'A'){    //If ch is lower than 'A' we add 'Z' and then substruct A + 1;
                        ch=ch+'Z'-'A'+1;
                    }   
                    message[i]=ch;
                }
            }
            printf("Encryped message is : %s\n",message);
            break;
        default:
            printf("\nInvalid Input!"); //Exits if number given is not 1 or 2
            exit(0);
    }

    
}

/*---------------------- HILL ----------------------*/




/*---------------------- AFFINE ----------------------*/
void Affine(){
    char msg[100];
    char cipher[100];
    int i,a,b,cho;
    int a_inv = 0;
    int flag = 0;

    printf("Whould you like to Encrypt or Decrypt the message?\n1.Encryption\n2.Decryption\n");
    scanf("%d",&cho);
    switch (cho){
    case 1:

        printf("Enter message to encrypt:\n");
        scanf("%s",msg);
        //Turning upper to lower
        for ( i = 0; i < strlen(msg); i++){
            if (msg[i]>=65 && msg[i]<=90){
                msg[i]+=32;
            }
        }
        printf("Message is: %s\n",msg);
        printf("Enter key a and b!\n");
        scanf("%d%d",&a,&b);
        printf("Key is %d and %d\n",a,b);

        ///Cipher Text initially empty
        for (i = 0; i < strlen(msg); i++){
            // Avoid space to be encrypted
            if(msg[i]!='\0'){
                /* Cryptography method is ( a x + b ) mod m
                x is msg[i] and m is 26 and added 97 ("A" in ascii) to
                bring it in range of ascii alphabet[ 97-122 | a-z ] */
                cipher[i] = cipher[i] +(char) ((((a * (msg[i]-97) ) + b) % 26) + 97);
            }else{
                //else simply append space character
                cipher[i] = (char)(32); //space character
            }    
        }
        printf("Encrypted  message is: \t");
        for (i = 0; i < strlen(msg); i++)        {
            printf("%c",cipher[i]); 
        }
        break;

    case 2:
        
        printf("Enter message to decrypt:\n");
        scanf("%s",cipher);
        for ( i = 0; i < strlen(cipher); i++){
            if (cipher[i]<=90 && cipher[i]>=65){
                cipher[i]+=32;
            }
        }
        printf("Encrypted message is: %s\n",cipher);
        printf("Enter key a and b!\n");
        scanf("%d%d",&a,&b);
        printf("Key is %d and %d\n",a,b);
        //Find a^-1 (the multiplicative inverse of a
        //in the group of integers modulo m.)
        for (i = 0; i < 26; i++)
        {
            flag = (a * i) % 26;
            //Check if (a*i)%26 == 1,
            //then i will be the multiplicative inverse of a
            if (flag == 1)
            {
                a_inv = i;
            }
        }
        for (i = 0; i < strlen(cipher); i++)
        {
            if(cipher[i]!='\0'){
                msg[i] = msg[i] + (char) (((a_inv * ((cipher[i]+ 97 - b)) % 26)) + 97);
                if(msg[i] <101){
                    msg[i]=(msg[i]+26)-4;
                }else{
                    msg[i]-=4;
                }
           }else{
                //else simply append space character
                msg[i] += cipher[i];
            }
        }
        for ( i = 0; i < strlen(cipher); i++)        {
            printf("%c",msg[i]);
        }
        
        break;
    default:
        printf("\nInvalid Input!"); //Exits if number given is not 1 or 2
        exit(0);
    }

}

/*---------------------- PERMUTATION ----------------------*/
void Permutation(){

    char message[100];
    int i=0,p=0,flag=0;
    int cho,n,j;
    /* I use the below to handle the ENTER from the menu
    because the new line is still on the buffer
    causing an error to my next gets() */
    gets(message);

    printf("Please enter the message: \n");
    gets(message); //the important one! :)
    printf("this is the message %s",message);
    /*It finds the N*N array we gonna need*/
    while ((flag==0) && i <= strlen(message)/2){
       if ( (i*i) >= strlen(message)){
            flag=1;
            n=i;
        }else{
            i++;
        }
    }
    printf("\n----- N= %d -----\n",n);
    int pin[n][n];
    printf("Whould you like to Encrypt or Decrypt the message?\n1.Encryption\n2.Decryption\n");
    scanf("%d",&cho);
    switch (cho)    {
    case 1:
    /*It starts from the first row for i=0 till j=0-(n-1)*/ 
        for ( i = 0; i < n; i++){
            for ( j = 0; j < n; j++){
                if (p >= strlen(message)){
                    pin[i][j]= (char) 32 ;
                    p++;
                }else{
                    pin[i][j]=(int) message[p] - 97;
                    p++;
                }
            }
        }

        //For the encryption we read from the first column for j=0 till i= 0-(n-1)*/ 
        printf("\nEncryption is\n");
        for ( j = 0; j < n; j++){
            for ( i = 0; i < n; i++){
                //Ignore spaces
                if (pin[i][j]!=32){
                    printf("%c",(char) (pin[i][j]+97));
                }else{
                    printf("%c",(char) (32));
                }
            }
        }
        break;
    case 2:
    /*We store the message the same way we did the encryption*/
        for ( j = 0; j < n; j++){
            for ( i = 0; i < n; i++){
                if (p >= strlen(message)){
                    pin[i][j]= (char) 32 ;
                    p++;
                }else{
                    pin[i][j]=(int) message[p] - 97;
                    p++;
                }
            }
        }
        //For the Decryption Vice Versa*/ 
        printf("Decryption is: \n");
        for ( i = 0; i < n; i++){
            for ( j = 0; j < n; j++){
                if (pin[i][j]!=32)
                {
                    printf("%c",(char) pin[i][j] + 97);
                }else{
                    printf("%c",(char) 32);
                }
            }
        }
        break;
    default:
        break;
        exit(0);
    }

}
/*---------------------- VIGENERE ----------------------*/
