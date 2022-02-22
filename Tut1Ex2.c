
//automatic initialization to 0
char buffer[256];

char arraypar(char* buffer){
	char cumulative = 0; //cumulative XOR of all characters in the buffer
	
	for(int i =0; i<256; i++){
		//XOR betweeen array buffer and the partial sum. the XOR keeps the parity
		//of each bit in each bit. Brilliant!
		cumulative = cumulative ^ buffer[i];
	}
	return cumulative;
	
}
int main(){
	buffer[0] = '$';
	buffer[1] = 'G';
	buffer[2] = 'P';
	printf("The result of the operation is 0x%x", arraypar(buffer)); 
}