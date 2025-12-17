#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD 1024

typedef struct {
	int height;
	const char* scale;
} Resolution;

Resolution resolutions[] = {
	{2160, "3840:2160"},
	{1440, "2560:1440"},
	{1080, "1920:1080"},
	{720, "1280:720"},
	{480, "854:480"},
	{360, "640:360"},
	{240, "426:240"},
	{144, "256:144"},
};

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input-video>\n", argv[0]);
		return 1;
	}
	const char* input = argv[1];
	char cmd[MAX_CMD];
	FILE* fp;
	int height = 0;
	snprintf(cmd, sizeof(cmd), "ffprobe -v error -select_streams v:0 -show_entries stream=height -of csv=p=0 \"%s\"", input);
	fp = popen(cmd, "r");
	if (!fp) {
		perror("Failed to run ffprobe");
		return 1;
	}
	if (fscanf(fp, "%d", &height) != 1) {
		fprintf(stderr, "Error: couldn't read video height\n");
		pclose(fp);
		return 1;
	}
	pclose(fp);
	printf("Input video height: %dpx\n", height);
	size_t count = sizeof(resolutions) / sizeof(resolutions[0]);
	for (size_t i = 0; i < count; ++i) {
		if (height >= resolutions[i].height) {
			char output[256];
			snprintf(output, sizeof(output), "output_%dp.mp4", resolutions[i].height);
			snprintf(cmd, sizeof(cmd), "ffmpeg -i \"%s\" -vf scale=%s -c:v libx264 -preset fast -crf 23 -c:a aac -b:a 128k -y \"%s\"", input, resolutions[i].scale, output);
			printf("Encoding %dp...\n", resolutions[i].height);
			int ret = system(cmd);
			if (ret != 0) {
				fprintf(stderr, "Error encoding %dp\n", resolutions[i].height);
			}
		}
	}
	printf("✅ Encoding complete!\n");
	return 0;
}
