#include <vector>
#include <iostream>
#include <string>

int N, M;
std::vector<std::string>field;
int minsteps = -1;



void marshrut(int x, int y, int steps, std::vector<std::vector<bool>>& visited) {
	if (x < 0 || x >= N || y < 0 || y >= M) {
		return;
	}
	if (field[x][y] == '#') {
		return;
	}
	if (visited[x][y]) {
		return;
	}

	if (field[x][y] == 'E') {
		if (minsteps == -1 || steps < minsteps) {
			minsteps = steps;
		}
		return;
	}
	visited[x][y] = true;

	marshrut(x - 1, y - 1, steps + 1, visited);
	marshrut(x - 1, y, steps + 1, visited);
	marshrut(x - 1, y + 1, steps + 1, visited);
	marshrut(x, y - 1, steps + 1, visited);
	marshrut(x, y + 1, steps + 1, visited);
	marshrut(x + 1, y - 1, steps + 1, visited);
	marshrut(x + 1, y, steps + 1, visited);
	marshrut(x + 1, y + 1, steps + 1, visited);

	visited[x][y] = false;
}

int main() {
	std::cin >> N >> M;

	for (int i = 0; i < N; i++) {
		std::string r;
		std::cin >> r;
		field.push_back(r);
	}

	int startX = -1, startY = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (field[i][j] == 'S') {
				startX = i;
				startY = j;
			}
		}
	}


	std::vector<std::vector<bool>>visited;
	for (int i = 0; i < N; i++) {
		std::vector<bool>r;
		for (int j = 0; j < M; j++) {
			r.push_back(false);
		}
		visited.push_back(r);
	}

	marshrut(startX, startY, 0, visited);
	std::cout << minsteps << std::endl;

	return 0;

}
