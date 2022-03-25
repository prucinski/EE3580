int parity(char c){
	char mask = 0x01; //AND mask as 0000 0001
	int count = 0;
	char maskRes;
	for(int i = 0; i <sizeof(char)*8; i++){
		maskRes = c & mask;
		if(maskRes == 0){
			count++;
		}
		//shift to the right, test last bit in a loop.
		c = c>>1;
	}
	return count% 2;
	}
	
	int main(){
		printf("Does character 'a' have even parity? %d Does character '8' have even parity? %d", parity('a'), parity(8));
		printf("What about 0x23? %d And what about 0xCA? %d",parity(0x23), parity(0xCA));
	}
	