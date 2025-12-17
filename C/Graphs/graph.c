#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
	if (gnuplotPipe == NULL) {
		printf("Error: Could not open pipe to gnuplot.\n");
		return 1;
	}
	// FILE *tempData = fopen("styled_data.txt", "w");
	// for (double x = 0; x <= 10; x += 0.1)
	// {
	//     fprintf(tempData, "%lf %lf\n", x, x * x);
	// }
	// fclose(tempData);
	fprintf(gnuplotPipe, "set title 'The Graph'\n");
	fprintf(gnuplotPipe, "set xlabel 'X-axis'\n");
	fprintf(gnuplotPipe, "set ylabel 'Y-axis'\n");
	fprintf(gnuplotPipe, "set zlabel 'Z-axis'\n");
	fprintf(gnuplotPipe, "plot sin(x) \n");
	// fprintf(gnuplotPipe, "plot 'styled_data.txt' with linespoints lt 3 lw 1 pt 7\n");
	pclose(gnuplotPipe);
	return 0;
}
