/*************************** project01.cpp *******************************/
// Michael Agnew, Project 01, CPE 212-01
// Purpose: Taking in an image and processing it in predetermined ways.
//
//******************************************************************

void LoadImage(const string imagefile, int image[MAXROWS][MAXCOLS])
{ // start of LoadImage function

	ifstream newfile; // declaring a new filestream
	newfile.open(imagefile.c_str()); // opening the file

	newfile.ignore(200, '\n'); // ignoring the first two lines to reach the array
	newfile.ignore(200, '\n');

	for (int i = 0; i < MAXROWS && !newfile.eof(); i++) // looping through the file and extracting each value into image until reaching the end of the file
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			newfile >> image[i][j];
		}
	}

} // end of LoadImage function

void FlipHorizontal(int image[MAXROWS][MAXCOLS])
{ // start of FlipHorizontal function
	for (int i = 0; i < MAXROWS; i++) {

		int first = 0; // initializing a variable "first" at 0

		int last = MAXCOLS - 1; // subtracting MAXCOLS by 1 to reach the last value

		while (first < last) // loop until first is as large as last
		{

			std::swap(image[i][first], image[i][last]);

			first++;
			last--;
		}
	}

} // end of FlipHorizontal function

void FlipVertical(int image[MAXROWS][MAXCOLS])
{ // start of FlipVertical function

	for (int i = 0; i < (MAXROWS / 2); i++)
	{
		for (int j = 0; j != MAXCOLS; j++)
		{
			std::swap(image[i][j], image[MAXROWS - 1 - i][j]);
		}
	}

} // end of FlipVertical function
void RotateCW(int image[MAXROWS][MAXCOLS])
{ // start of RotateCW function

	int Rotate_CW[MAXROWS][MAXCOLS]; // initializing an empty array

	for (int i = 0; i < MAXCOLS; i++)
	{
		for (int j = 0; j < MAXROWS; j++)
		{
			Rotate_CW[i][j] = image[MAXROWS - 1 - j][i]; // putting values from image into the rotate array
		}
	}
	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			image[i][j] = Rotate_CW[i][j]; // putting the values from the rotate array back into the image array
		}
	}


} // end of RotateCW function
void RotateCCW(int image[MAXROWS][MAXCOLS])
{ // start of RotateCCW function
	int Rotate_CCW[MAXROWS][MAXCOLS]; // initializing an empty array to store values

	for (int i = 0; i < MAXCOLS; i++)
	{
		for (int j = 0; j < MAXROWS; j++)
		{
			Rotate_CCW[i][j] = image[MAXROWS - 1 - j][i]; // rotating the image
		}
	}

	int next[MAXROWS][MAXCOLS]; // initializing another empty array to store values

	for (int i = 0; i < MAXCOLS; i++)
	{
		for (int j = 0; j < MAXROWS; j++)
		{
			next[i][j] = Rotate_CCW[MAXROWS - 1 - j][i]; // rotating the image again
		}
	}
	int final[MAXROWS][MAXCOLS]; // initializing the last empty array

	for (int i = 0; i < MAXCOLS; i++)
	{
		for (int j = 0; j < MAXROWS; j++)
		{
			final[i][j] = next[MAXROWS - 1 - j][i]; // rotating the image a third time
		}
		for (int i = 0; i < MAXROWS; i++)
		{
			for (int j = 0; j < MAXCOLS; j++)
			{
				image[i][j] = final[i][j]; // inputting the final CCW rotated image back into the image array
			}
		}
	}

} // end of RotateCCW function
void Transpose(int image[MAXROWS][MAXCOLS])
{ // start of Transpose function
	int transposer[MAXROWS][MAXCOLS]; // initializing an empty array to store values

	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			transposer[j][i] = image[i][j]; // swapping the index values to transpose the array
		}
	}

	for (int i = 0; i < MAXROWS; i++)
	{
		for (int j = 0; j < MAXCOLS; j++)
		{
			image[j][i] = transposer[j][i]; // inputting the values from the transposed array back into the image array
		}
	}
} // end of Transpose function
