#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
struct DataBase {
	char Bus[10][50];
	int numBus;
	int numStop[10];
	char Stop[10][30][50];
}num1;
FILE* file2;
int Ravstr(int k1, int k2)
{
	int jec = 1;
	int itog = 0;
	for (int i = 0; i < num1.numStop[k1]; i++)
		for (int j = 0; j < num1.numStop[k2]; j++)
		{
			jec = 1;
			for (int z = 0; z < num1.numStop[k1] || z < num1.numStop[k2]; z++)
			{
				if (num1.Stop[k1][i][z] != num1.Stop[k2][j][z])
				{
					z = 100;
					jec = 0;

				}
			}
			if (jec == 1)
			{
				itog = 1;
			}
		}
	return itog;

}
void PrintBus(char* name)
{
	file2 = fopen("output.txt", "a");
	int c = -1;
	int b = 0;
	for (int i = 0; i < num1.numBus; i++)
	{
		b = 1;
		for (int j = 0; (num1.Bus[i][j] > 21 && num1.Bus[i][j] < 255) || (name[j] > 21 && name[j] < 255); j++)
		{
			if (num1.Bus[i][j] != name[j])
			{
				b = 0;
				break;
			}
		}
		if (b == 1)
			c = i;
	}
	if (c > -1)
	{
		fprintf(file2, "%s\n", name);
		fprintf(file2, "STOPS: ");
		for (int i = 0; i < num1.numStop[c]; i++)
		{
			fprintf(file2, "%s ", num1.Stop[c][i]);
		}
		fprintf(file2, "\n");
	}
	else
		fprintf(file2, "BUS %s DOESN'T EXIST\n", name);
	fclose(file2);
}
void Find(char* name1, char* name2)
{
	file2 = fopen("output.txt", "a");
	int delt = 1;
	int d = 0;
	for (int i = 0; i < sizeof(name1) && i < sizeof(name2); i++)
	{
		if (name1[i] != name2[i])
		{
			delt = 0;
			break;
		}
	}
	if (delt == 1)
	{
		fprintf(file2, "STOPS %s ARE THE SAME\n", name1);
	}
	else
	{
		for (int i = 0; i < num1.numBus; i++)
		{
			int c1 = 0;
			int c2 = 0;
			for (int j = 0; j < num1.numStop[i]; j++)
			{
				int m1 = 1;
				int m2 = 1;
				for (int z = 0; z < sizeof(name1); z++)
				{
					if (num1.Stop[i][j][z] != name1[z])
						m1 = 0;
					if (num1.Stop[i][j][z] != name2[z])
						m2 = 0;
				}
				if (m1 == 1)
					c1 = 1;
				if (m2 == 1)
					c2 = 1;
			}
			if (c1 == 1 && c2 == 1)
			{
				if (d == 0)
				{
					fprintf(file2, "BUSES FROM %s TO %s:\n", name1, name2);
				}
				fprintf(file2, "%s\n", num1.Bus[i]);
				d++;
			}
		}
		if (d == 0)
		{
			int b1 = 0;
			int b2 = 0;
			int mas1[10] = { 0 };
			int mas2[10] = { 0 };
			for (int i = 0; i < 10; i++)
			{
				mas1[i] = -1;
				mas2[i] = -1;
			}

			for (int i = 0; i < num1.numBus; i++)
			{
				for (int j = 0; j < num1.numStop[i]; j++)
				{
					int n = 1;
					for (int z = 0; name1[z] != '\0'; z++)
					{
						if (num1.Stop[i][j][z] != name1[z])
						{
							n = 0;
							break;
						}
					}
					if (n == 1)
					{
						mas1[i] = i;
						b1++;
					}
					n = 1;
					for (int z = 0; name2[z] != '\0'; z++)
					{
						if (num1.Stop[i][j][z] != name2[z])
						{
							n = 0;
							break;
						}
					}
					if (n == 1)
					{
						mas2[i] = i;
						b2++;
					}
				}
			}
			if (b1 > 0 && b2 > 0)
			{
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (mas2[j] != -1 && mas1[i] != -1)
						{
							int ushaz = Ravstr(i, j);
							if (ushaz == 1)
							{
								if (d == 0)
								{
										fprintf(file2, "BUSES FROM %s TO %s:\n", name1, name2);
										d = 1;
								}
								if(d!=0)
								{
									if (i < j)
									{
										fprintf(file2, "%s %s\n", num1.Bus[mas1[i]], num1.Bus[mas2[j]]);
									}
									else
									{
										fprintf(file2, "%s %s\n", num1.Bus[mas2[j]], num1.Bus[mas1[i]]);

									}
								}
							}
						}
					}
				}
			}
		}
		if (d == 0)
		{
			fprintf(file2, "THERE ARE NO BUSES FROM %s TO %s\n", name1, name2);
		}
	}
	fclose(file2);
}
void PrintStop(char* name)
{
	file2 = fopen("output.txt", "a");
	int c = 0;
	int u = 1;
	fprintf(file2, "%s: ", name);
	for (int i = 0; i < num1.numBus; i++)
	{
		for (int j = 0; j < num1.numStop[i]; j++)
		{
			u = 1;
			for (int z = 0; z < sizeof(name); z++)
				if (num1.Stop[i][j][z] != name[z])
				{
					u = 0;
					break;
				}
			if (u == 1)
			{

				fprintf(file2, "%s ", num1.Bus[i]);
				c++;
			}

		}
	}
	if (c == 0)
		fprintf(file2, "NO BUSES GO TO STOP\n");
	else
		fprintf(file2, "\n");
	fclose(file2);
}
void PrintAll()
{
	file2 = fopen("output.txt", "a");
	for (int i = 0; i < num1.numBus; i++)
	{
		fprintf(file2, "%s\n", num1.Bus[i]);
		fprintf(file2, "STOPS: ");
		for (int j = 0; j < num1.numStop[i]; j++)
		{
			fprintf(file2, "%s ", num1.Stop[i][j]);
		}
		fprintf(file2, "\n");

	}
	fclose(file2);
}
void addStop(char* nameB, char* nameS)
{
	file2 = fopen("output.txt", "a");
	int c = -1;
	int b = 0;
	for (int i = 0; i < num1.numBus; i++)
	{
		b = 1;
		for (int j = 0; (num1.Bus[i][j] > 21 && num1.Bus[i][j] < 255) || (nameB[j] > 21 && nameB[j] < 255); j++)
		{
			if (num1.Bus[i][j] != nameB[j])
			{
				b = 0;
				break;
			}
		}
		if (b == 1)
			c = i;
	}
	if (c == -1)
		fprintf(file2, "BUS %s DOESN'T EXIST\n", nameB);
	else
	{
		if (num1.numStop[c] < 30)
		{
			int g = 1;
			int fg = 0;
			for (int i = 0; i < num1.numStop[c]; i++)
			{
				g = 1;
				for (int j = 0; (num1.Stop[c][i][j] > 21 && num1.Stop[c][i][j] < 255) || (nameS[j] > 21 && nameS[j] < 255); j++)
				{
					if (num1.Stop[c][i][j] != nameS[j])
					{
						g = 0;
						break;
					}

				}
				if (g == 1)
				{
					fg = 1;
				}
			}
			if (fg == 1)
			{
				fprintf(file2, "BUS %s ALREADY HAS STOP %s\n", nameB, nameS);
			}
			else {
				for (int i = 0; nameS[i] > 21 && nameS[i] < 255; i++)
				{
					num1.Stop[c][num1.numStop[c]][i] = nameS[i];
				}
				num1.numStop[c]++;
			}
		}
		else
		{
			fprintf(file2, "CAN'T ADD STOP %s TO BUS %s. BUS IS FULL\n", nameS, nameB);
		}

	}
	fclose(file2);
}
void addBus(char* name)
{
	file2 = fopen("output.txt", "a");
	int c = 0;
	if (num1.numBus < 10)
	{
		int b = 0;
		for (int i = 0; i < num1.numBus; i++)
		{
			b = 1;
			for (int j = 0; (num1.Bus[i][j] > 21 && num1.Bus[i][j] < 255) || (name[j] > 21 && name[j] < 255); j++)
			{
				if (num1.Bus[i][j] != name[j])
				{
					b = 0;
					break;
				}
			}
			if (b == 1)
				c = 1;
		}
		if (c == 0)
		{
			for (int i = 0; name[i] > 21 && name[i] < 255; i++)
			{
				num1.Bus[num1.numBus][i] = name[i];
			}
			num1.numBus++;
		}
		else
			fprintf(file2, "BUS %s ALREADY EXISTS\n", name);
	}
	else
		fprintf(file2, "CAN'T ADD BUS %s. BUSPARK IS FULL\n", name);
	fclose(file2);
}
int main()
{
	num1.numBus = 0;
	for (int i = 0; i < 10; i++)
	{
		num1.numStop[i] = 0;
	}
	char a = ' ';
	FILE* file;
	file = fopen("input.txt", "r");
	file2 = fopen("output.txt", "w");
	while ((!feof(file)))
	{
		char String[50] = "";
		char String2[50] = "";
		char String3[50] = "";
		char String4[50] = "";
		char String5[50] = "";
		int i = 0;
		int j = 0;
		while (a != '\n')
		{

			if (feof(file))
				break;
			fscanf(file, "%c", &a);
			if (a == '\n')
			{
				break;
			}
			if (a == ' ')
			{
				i = 0;
				j++;
			}
			else
			{


				if (j == 0)
					String[i] = a;
				else if (j == 1)
					String2[i] = a;
				else if (j == 2)
					String3[i] = a;
				else if (j == 3)
					String4[i] = a;
				else if (j == 4)
					String5[i] = a;
				i++;
			}
			a = ' ';
		}
		if (String[0] == 'A' && String[1] == 'D' && String[2] == 'D')
		{
			if (String2[0] == 'B' && String2[1] == 'U' && String2[2] == 'S' && String4[0] == '\0' && String3[0] != '\0')
			{
				addBus(String3);
			}
			else if (String2[0] == 'S' && String2[1] == 'T' && String2[2] == 'O' && String2[3] == 'P' && String4[0] != '\0' && String3[0] != '\0' && String5[0] == '\0')
			{
				addStop(String3, String4);
			}
			else
			{
				file2 = fopen("output.txt", "a");
				fprintf(file2, "WRONG ADD FORMAT\n");
				fclose(file2);
			}
		}
		else if (String[0] == 'P' && String[1] == 'R' && String[2] == 'I' && String[3] == 'N' && String[4] == 'T')
		{
			if (String2[0] == 'A' && String2[1] == 'L' && String2[2] == 'L' && String3[0] == '\0')
			{
				PrintAll();
			}
			else if (String2[0] == 'B' && String2[1] == 'U' && String2[2] == 'S' && String4[0] == '\0' && String3[0] != '\0')
			{
				PrintBus(String3);
			}
			else if (String2[0] == 'S' && String2[1] == 'T' && String2[2] == 'O' && String2[3] == 'P' && String4[0] == '\0' && String3[0] != '\0')
			{
				PrintStop(String3);
			}
			else {
				file2 = fopen("output.txt", "a");
				fprintf(file2, "WRONG PRINT FORMAT\n");
				fclose(file2);

			}

		}
		else if (String[0] == 'F' && String[1] == 'I' && String[2] == 'N' && String[3] == 'D')
		{
			if (String4[0] == '\0' && String2[0] != '\0' && String3[0] != '\0')
				Find(String2, String3);
			else
			{
				file2 = fopen("output.txt", "a");
				fprintf(file2, "WRONG FIND FORMAT\n");
				fclose(file2);
			}
		}
		a = ' ';
	}


}