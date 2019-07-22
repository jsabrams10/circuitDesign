#include<stdio.h>

#include<stdlib.h>

#include<string.h>


// AUXILIARY FUNCTIONS

	// DIRECTIVES

int not(int in){

	if(in == 0){			return 1;}
	
	else if(in == 1){		return 0;}

	return -1;
}

int and(int inA, int inB){

	if(inA == 0){

		if(inB == 0){		return 0;}

		else if(inB == 1){	return 0;}
	}

	else if(inA == 1){

		if(inB == 0){		return 0;}

		else if(inB == 1){	return 1;}
	}

	return -1;
}

int or(int inA, int inB){

	if(inA == 0){

		if(inB == 0){		return 0;}

		else if(inB == 1){	return 1;}
	}

	else if(inA == 1){

		if(inB == 0){		return 1;}

		else if(inB == 1){	return 1;}
	}

	return -1;
}

int nand(int inA, int inB){

	int andAB = -1;

	andAB = and(inA, inB);

	int notAndAB = -1;

	notAndAB = not(andAB);

	return notAndAB;
}

int nor(int inA, int inB){

	int orAB = -1;

	orAB = or(inA, inB);

	int notOrAB = -1;

	notOrAB = not(orAB);

	return notOrAB;
}

int xor(int inA, int inB){

	if(inA == 0){

		if(inB == 0){		return 0;}

		else if(inB == 1){	return 1;}
	}

	else if(inA == 1){

		if(inB == 0){		return 1;}

		else if(inB == 1){	return 0;}
	}

	return -1;
}

int pass(int in){			return in;}

int multiplexer(int** inArr){		return -1;}


	// STRING CONCATENATION

char* getCatStr(char* str1, char* str2){

	int resultLen = 0;

	if(str1){	resultLen += strlen(str1);}

	if(str2){	resultLen += strlen(str2);}

	char* result = malloc((resultLen + 1) * sizeof(char));

	if(str1 || str2){

		*result = '\0';

		if(str1){	strcpy(result, str1);}

		if(str2){	strcat(result, str2);}
	}

	return result;
}

int main(int argc, char* argv[]){

	char* fileName;

	fileName = argv[1];

	FILE* filePass1 = fopen(fileName, "r");

	// VARIABLE DECLARATIONS

		// FILE VARIABLES

	char* fileStr = NULL;

	char* directive = malloc(17 * sizeof(char));

		// INPUT VARIABLES

	int numIn = 0;

	int* input = malloc(sizeof(int*));

	char** inputLookup = malloc(sizeof(char**));

		// OUTPUT VARIABLES

	int numOut = 0;

	int* output = malloc(sizeof(int*));

	char** outputLookup = malloc(sizeof(char**));

		// TEMPORARY VARIABLES

	int numTemp = 0;

	int* temp = malloc(sizeof(int*));

	char** tempLookup = malloc(sizeof(char**));


	while(fscanf(filePass1, " %16s", directive) != EOF){

		//printf("%s\n", directive);

		if(strcmp(directive, "INPUT") == 0){

			fileStr = getCatStr(fileStr, "INPUT ");

			fscanf(filePass1, " %d", &numIn);

			//printf("%d\n", numIn);

			char numInStr[17];

			sprintf(numInStr, "%d", numIn);

			fileStr = getCatStr(fileStr, numInStr);

			fileStr = getCatStr(fileStr, " ");

			input = realloc(input, numIn * sizeof(int));

			inputLookup = realloc(inputLookup, numIn * 17 * sizeof(char));

			int nextVarDex = 0;

			for(; nextVarDex < numIn; nextVarDex++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				fileStr = getCatStr(fileStr, nextVar);

				fileStr = getCatStr(fileStr, " ");

				inputLookup[nextVarDex] = nextVar;
			}

			//int testDex = 0;

			//for(; testDex < numIn; testDex++){

				//printf("%s\n", inputLookup[testDex]);
			//}
		}

		else if(strcmp(directive, "OUTPUT") == 0){

			fileStr = getCatStr(fileStr, "OUTPUT ");

			fscanf(filePass1, " %d", &numOut);

			//printf("%d\n", numOut);

			char numOutStr[17];

			sprintf(numOutStr, "%d", numOut);

			fileStr = getCatStr(fileStr, numOutStr);

			fileStr = getCatStr(fileStr, " ");

			output = realloc(output, numOut * sizeof(int));

			outputLookup = realloc(outputLookup, numOut * 17 * sizeof(char));

			int nextVarDex = 0;

			for(; nextVarDex < numOut; nextVarDex++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				fileStr = getCatStr(fileStr, nextVar);

				fileStr = getCatStr(fileStr, " ");

				outputLookup[nextVarDex] = nextVar;
			}

			//int testDex = 0;

			//for(; testDex < numOut; testDex++){

				//printf("%s\n", outputLookup[testDex]);
			//}
		}

		else if(strcmp(directive, "NOT") == 0){

			fileStr = getCatStr(fileStr, "NOT ");

			int countToTwo = 1;

			for(; countToTwo <= 2; countToTwo++){

				char* nextVar = malloc(17 * sizeof(char));

        	                fscanf(filePass1, "%*[: ]%16s", nextVar);

				if(strcmp(nextVar, "0") == 0){

					fileStr = getCatStr(fileStr, "0");

					continue;
				}

				else if(strcmp(nextVar, "1") == 0){

					fileStr = getCatStr(fileStr, "1");

					continue;
				}

				char* varDexStr = malloc(17 * sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}
		}

		else if(strcmp(directive, "AND") == 0){

			fileStr = getCatStr(fileStr, "AND ");

			int countToThree = 1;

			for(; countToThree <= 3; countToThree++){

				char* nextVar = malloc(17 * sizeof(char));

				fileStr = getCatStr(fileStr, nextVar);

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				if(strcmp(nextVar, "0") == 0){

					fileStr = getCatStr(fileStr, "0 ");

					continue;
				}

				else if(strcmp(nextVar, "1") == 0){

					fileStr = getCatStr(fileStr, "1 ");

					continue;
				}

				char* varDexStr = malloc(17 * sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char*));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}
		}

		else if(strcmp(directive, "OR") == 0){

			fileStr = getCatStr(fileStr, "OR ");

			int countToThree = 1;

                        for(; countToThree <= 3; countToThree++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				if(strcmp(nextVar, "0") == 0){

					fileStr = getCatStr(fileStr, "0 ");

					continue;
				}

				else if(strcmp(nextVar, "1") == 0){

					fileStr = getCatStr(fileStr, "1 ");

					continue;
				}

				char* varDexStr = malloc(17 * sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char*));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}
		}

		else if(strcmp(directive, "NAND") == 0){

			fileStr = getCatStr(fileStr, "NAND ");

			int countToThree = 1;

			for(; countToThree <= 3; countToThree++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				if(strcmp(nextVar, "0") == 0){

					fileStr = getCatStr(fileStr, "0 ");

					continue;
				}

				else if(strcmp(nextVar, "1") == 0){

					fileStr = getCatStr(fileStr, "1 ");

					continue;
				}

				char* varDexStr = malloc(167* sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char*));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}
		}

		else if(strcmp(directive, "NOR") == 0){

			fileStr = getCatStr(fileStr, "NOR ");

			int countToThree = 1;

			for(; countToThree <= 3; countToThree++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				if(strcmp(nextVar, "0") == 0){

					fileStr = getCatStr(fileStr, "0 ");

					continue;
				}

				else if(strcmp(nextVar, "1") == 0){

					fileStr = getCatStr(fileStr, "1 ");

					continue;
				}

				char* varDexStr = malloc(17 * sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char*));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}
		}

		else if(strcmp(directive, "XOR") == 0){

			fileStr = getCatStr(fileStr, "XOR ");

			int countToThree = 1;

			for(; countToThree <= 3; countToThree++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				if(strcmp(nextVar, "0") == 0){

					fileStr = getCatStr(fileStr, "0 ");

					continue;
				}

				else if(strcmp(nextVar, "1") == 0){

					fileStr = getCatStr(fileStr, "1 ");

					continue;
				}

				char* varDexStr = malloc(17 * sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char*));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}
		}

		else if(strcmp(directive, "PASS") == 0){

			fileStr = getCatStr(fileStr, "PASS ");

			int countToTwo = 1;

			for(; countToTwo <= 2; countToTwo++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				if(strcmp(nextVar, "0") == 0){

					fileStr = getCatStr(fileStr, "0 ");

					continue;
				}

				else if(strcmp(nextVar, "1") == 0){

					fileStr = getCatStr(fileStr, "1 ");

					continue;
				}

				char* varDexStr = malloc(17 * sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}
		}

		else if(strcmp(directive, "DECODER") == 0){

			fileStr = getCatStr(fileStr, "DECODER ");

			int n = 0;

			fscanf(filePass1, " %d", &n);

			char* nStr = malloc(17 * sizeof(char));

			sprintf(nStr, "%d", n);

			fileStr = getCatStr(fileStr, nStr);

			fileStr = getCatStr(fileStr, " ");

			int countToN = 1;

			for(; countToN <= n; countToN++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				char* varDexStr = malloc(17 * sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char*));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}

			int twoToTheN = 1;

			for(countToN = 1; countToN <= n; countToN++){

				twoToTheN *= 2;
			}

			char* twoToTheNStr = malloc(17 * sizeof(char));

			sprintf(twoToTheNStr, "%d", twoToTheN);

			fileStr = getCatStr(fileStr, twoToTheNStr);

			fileStr = getCatStr(fileStr, " ");

			int countToTwoToTheN = 1;

			for(; countToTwoToTheN <= twoToTheN; countToTwoToTheN++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				char* varDexStr = malloc(17 * sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char*));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}
		}

		else if(strcmp(directive, "MULTIPLEXER") == 0){

			fileStr = getCatStr(fileStr, "MULTIPLEXER ");

			int n = 0;

			fscanf(filePass1, " %d", &n);

			int twoToTheN = 1;

			int countToN = 1;

			for(; countToN <= n; countToN++){

				twoToTheN *= 2;
			}

			char* twoToTheNStr = malloc(17 * sizeof(char));

			sprintf(twoToTheNStr, "%d", twoToTheN);

			fileStr = getCatStr(fileStr, twoToTheNStr);

			fileStr = getCatStr(fileStr, " ");

			int countToTwoToTheN = 1;

			for(; countToTwoToTheN <= twoToTheN; countToTwoToTheN++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				if(strcmp(nextVar, "0") == 0){

					fileStr = getCatStr(fileStr, "0 ");

					continue;
				}

				else if(strcmp(nextVar, "1") == 0){

					fileStr = getCatStr(fileStr, "1 ");

					continue;
				}

				char* varDexStr = malloc(17 * sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char*));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}

			char* nStr = malloc(17 * sizeof(char));

			sprintf(nStr, "%d", n);

			fileStr = getCatStr(fileStr, nStr);

			fileStr = getCatStr(fileStr, " ");

			int countToNPlusOne = 1;

			for(; countToNPlusOne <= n + 1; countToNPlusOne++){

				char* nextVar = malloc(17 * sizeof(char));

				fscanf(filePass1, "%*[: ]%16s", nextVar);

				if(strcmp(nextVar, "0") == 0){

					fileStr = getCatStr(fileStr, "0 ");

					continue;
				}

				else if(strcmp(nextVar, "1") == 0){

					fileStr = getCatStr(fileStr, "1 ");

					continue;
				}

				char* varDexStr = malloc(17 * sizeof(char));

				int isInput = 0;

				int isTemp = 1;

				int testDex = 0;

				for(; testDex < numIn; testDex++){

					if(strcmp(nextVar, inputLookup[testDex]) == 0){

						sprintf(varDexStr, "%d", 2 + testDex);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						isInput = 1;

						isTemp = 0;

						break;
					}
				}

				if(!isInput){

					for(testDex = 0; testDex < numOut; testDex++){

						if(strcmp(nextVar, outputLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isTemp = 0;

							break;
						}
					}
				}

				if(isTemp){

					int isNewTemp = 1;

					for(testDex = 0; testDex < numTemp; testDex++){

						if(strcmp(nextVar, tempLookup[testDex]) == 0){

							sprintf(varDexStr, "%d", 2 + numIn + numOut + testDex);

							fileStr = getCatStr(fileStr, varDexStr);

							fileStr = getCatStr(fileStr, " ");

							isNewTemp = 0;

							break;
						}
					}

					if(isNewTemp){

						numTemp++;

						char* workingTempLookup[numTemp];

						int nextVarDex = 0;

						for(; nextVarDex < numTemp - 1; nextVarDex++){

							workingTempLookup[nextVarDex] = tempLookup[nextVarDex];
						}

						workingTempLookup[numTemp - 1] = nextVar;

						temp = realloc(temp, numTemp * sizeof(int));

						tempLookup = realloc(tempLookup, numTemp * 17 * sizeof(char*));

						for(nextVarDex = 0; nextVarDex < numTemp; nextVarDex++){

							tempLookup[nextVarDex] = workingTempLookup[nextVarDex];
						}

						sprintf(varDexStr, "%d", 2 + numIn + numOut + numTemp - 1);

						fileStr = getCatStr(fileStr, varDexStr);

						fileStr = getCatStr(fileStr, " ");

						//printf("temp: %s\n", tempLookup[numTemp - 1]);
					}
				}
			}
		}
	}

	int* vars = malloc((2 + numIn + numOut + numTemp) * sizeof(int));

	vars[0] = 0;

	vars[1] = 1;

	char** varsLookup = malloc((2 + numIn + numOut + numTemp) * 17 * sizeof(char));

	varsLookup[0] = "0";

	varsLookup[1] = "1";

	int tempDex = 0;

	for(; tempDex < numIn; tempDex++){

		vars[tempDex + 2] = input[tempDex];

		varsLookup[tempDex + 2] = inputLookup[tempDex];
	}

	for(tempDex = 0; tempDex < numOut; tempDex++){

		vars[tempDex + 2 + numIn] = output[tempDex];

		varsLookup[tempDex + 2 + numIn] = outputLookup[tempDex];
	}

	for(tempDex = 0; tempDex < numTemp; tempDex++){

		vars[tempDex + 2 + numIn + numOut] = temp[tempDex];

		varsLookup[tempDex + 2 + numIn + numOut] = tempLookup[tempDex];
	}

	int numRows = 2;

	int pow1 = 1;

	for(; pow1 < numIn; pow1++){

		numRows *= 2;
	}

	int currRow = 1;

	for(; currRow <= numRows; currRow++){

		int currCol = 0;

		for(; currCol < numIn; currCol++){

			int x = currRow;

			int y = numRows;

			int pow2 = 0;

			for(; pow2 <= currCol; pow2++){

				y /= 2;
			}

			int z = 0;

			while(x > y){

				x -= y;
				z++;
			}

			if(z % 2 == 0){		vars[currCol + 2] = 0;}

			else if(z % 2 == 1){	vars[currCol + 2] = 1;}
		}

		int fileStrLen = strlen(fileStr);

		char* fileStrCopy = malloc((fileStrLen + 1) * sizeof(char));

		strcpy(fileStrCopy, fileStr);

		char* currTok = malloc(17 * sizeof(char));

		currTok = strtok(fileStrCopy, " ");

		while(currTok != NULL){

			//directive = strtok(NULL, " ");

			if(strcmp(currTok, "INPUT") == 0){

				int count = 1;

				for(; count <= numIn; count++){

					currTok = strtok(NULL, " ");
				}
			}

			if(strcmp(currTok, "OUTPUT") == 0){

				int count = 1;

				for(; count <= numOut; count++){

					currTok = strtok(NULL, " ");
				}
			}

			if(strcmp(currTok, "NOT") == 0){

				currTok = strtok(NULL, " ");

				int srcDex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int destDex = atoi(currTok);

				vars[destDex] = not(vars[srcDex]);
			}

			if(strcmp(currTok, "AND") == 0){

				currTok = strtok(NULL, " ");

				int src1Dex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int src2Dex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int destDex = atoi(currTok);

				vars[destDex] = and(vars[src1Dex], vars[src2Dex]);
			}

			if(strcmp(currTok, "OR") == 0){

				currTok = strtok(NULL, " ");

				int src1Dex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int src2Dex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int destDex = atoi(currTok);

				vars[destDex] = or(vars[src1Dex], vars[src2Dex]);
			}

			if(strcmp(currTok, "NAND") == 0){

				currTok = strtok(NULL, " ");

				int src1Dex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int src2Dex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int destDex = atoi(currTok);

				vars[destDex] = nand(vars[src1Dex], vars[src2Dex]);
			}

			if(strcmp(currTok, "NOR") == 0){

				currTok = strtok(NULL, " ");

				int src1Dex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int src2Dex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int destDex = atoi(currTok);

				vars[destDex] = nor(vars[src1Dex], vars[src2Dex]);
			}

			if(strcmp(currTok, "XOR") == 0){

				currTok = strtok(NULL, " ");

				int src1Dex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int src2Dex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int destDex = atoi(currTok);

				vars[destDex] = xor(vars[src1Dex], vars[src2Dex]);
			}

			if(strcmp(currTok, "PASS") == 0){

				currTok = strtok(NULL, " ");

				int srcDex = atoi(currTok);

				currTok = strtok(NULL, " ");

				int destDex = atoi(currTok);

				vars[destDex] = pass(vars[srcDex]);
			}

			if(strcmp(currTok, "DECODER") == 0){

				currTok = strtok(NULL, " ");

				int n = atoi(currTok);

				char* sStr = malloc((n + 1) * sizeof(char));

				int bitDex = 0;

				for(; bitDex < n; bitDex++){

					currTok = strtok(NULL, " ");

					int inputDex = atoi(currTok);

					if(vars[inputDex] == 0){	sStr[bitDex] = '0';}

					else if(vars[inputDex] == 1){	sStr[bitDex] = '1';} 
				}

				int sInt = (int)strtol(sStr, NULL, 2);

				currTok = strtok(NULL, " ");

				int twoToTheN = atoi(currTok);

				for(bitDex = 0; bitDex < twoToTheN; bitDex++){

					currTok = strtok(NULL, " ");

					int outputDex = atoi(currTok);

					if(bitDex == sInt){	vars[outputDex] = 1;}

					else{			vars[outputDex] = 0;}
				}	
			}

			if(strcmp(currTok, "MULTIPLEXER") == 0){

				currTok = strtok(NULL, " ");

				int twoToTheN = atoi(currTok);

				int inputDexes[twoToTheN];

				int currDex = 0;

				for(; currDex < twoToTheN; currDex++){

					currTok = strtok(NULL, " ");

					inputDexes[currDex] = atoi(currTok);
				}

				currTok = strtok(NULL, " ");

				int n = atoi(currTok);

				int selectorVal = 0;

				int pow = n - 1;

				int bitDex = 0;

				for(; bitDex < n; bitDex++){

					currTok = strtok(NULL, " ");

					int varDex = atoi(currTok);

					int bitVal = vars[varDex];

					if(bitVal == 1){

						int getToPow = 1;

						for(; getToPow <= pow; getToPow++){

							bitVal *= 2;
						}

					}

					selectorVal += bitVal;

					pow--;
				}

				currTok = strtok(NULL, " ");

				int destDex = atoi(currTok);

				vars[destDex] = vars[inputDexes[selectorVal]];
			}

			currTok = strtok(NULL, " ");
		}

		int printDex = 2;

		for(; printDex < 2 + numIn; printDex++){

			printf("%d ", vars[printDex]);
		}

		printf("|");

		for(; printDex < 2 + numIn + numOut; printDex++){

			printf(" %d", vars[printDex]);
		}

		printf("\n");
	}

	//printf("Here's our fileStr: %s", fileStr);

	return EXIT_SUCCESS;
}
