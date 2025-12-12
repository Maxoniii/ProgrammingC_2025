#include "func.hpp"
#include <iostream>
#include <vector>

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::string> field(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> field[i];
    }

    int result = minSteps(field, N, M);

    std::cout << result << std::endl;

    return 0;
}





#include "func.hpp"
#include <vector>


int minSteps(std::vector<std::string>& field, int N, int M) {
	Coordinate start, end;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field[i][j] == 'S') {
				start.x = i;
				start.y = j;
				field[i][j] = '.';
			}
			else if (field[i][j] == 'E') {
				end.x = i;
				end.y = j;
				field[i][j] = '.';
			}
		}
	}

	std::vector<std::vector<bool>> visit(N, std::vector<bool>(M, false));
	struct Rast {
		int x, y, steps;
	};

	std::vector<Rast>rast;
	rast.reserve(N * M);
	rast.push_back({ start.x,start.y,0 });
	visit[start.x][start.y] = true;

	int head = 0;
	int dx[8] = { -1,-1,-1,0,0,1,1,1 };
	int dy[8] = { -1,0,1,-1,1,-1,0,1 };

	while (head < rast.size()) {
		Rast nast = rast[head];
		head++;

		if (nast.x == end.x && nast.y == end.y) {
			return nast.steps;
		}

		for (int i = 0; i < 8; i++) {
			int nx = nast.x + dx[i];
			int ny = nast.y + dy[i];

			if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
				if (field[nx][ny] == '.' && !visit[nx][ny]) {
					visit[nx][ny] = true;
					rast.push_back({ nx,ny,nast.steps + 1 });
				}
			}
		}
	}
	return -1;
}







#pragma once
#include <vector>
#include <string>
struct Coordinate {
	int x, y;
};

int minSteps(std::vector<std::string>& field, int N, int M);