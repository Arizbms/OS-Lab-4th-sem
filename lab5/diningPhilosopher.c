#include <stdio.h>

#define N 5

int forks[N] = {1, 1, 1, 1, 1};
int finished[N] = {0};

void wait(int *sem) {
  while (*sem <= 0);
  (*sem)--;
}

void signal(int *sem) {
  (*sem)++;
}

void think(int i) {
  printf("Philosopher %d is thinking\n", i + 1);
}

void eat(int i) {
  wait(&forks[i]);
  wait(&forks[(i + 1) % N]);
  printf("Philosopher %d is eating\n", i + 1);
  signal(&forks[i]);
  signal(&forks[(i + 1) % N]);
  finished[i] = 1;
}

int forks_available(int i) {
  return forks[i] && forks[(i + 1) % N];
}

int overlap(int i, int j) {
  return i == j || i == (j + 1) % N || (i + 1) % N == j || (i + 1) % N == (j + 1) % N;
}

void simulate_one_eating() {
  printf("\nSimulation: One philosopher eats at a time\n");
  for (int i = 0; i < N; i++) {
    if (!finished[i]) {
      think(i);
      eat(i);
    }
  }
}

void simulate_two_eating() {
  printf("\nSimulation: Two philosophers eat at a time\n");
  int remaining = N;

  while (remaining > 0) {
    int ate = 0;

    for (int i = 0; i < N; i++) {
      if (!finished[i]) {
        int paired = 0;

        for (int j = i + 1; j < N; j++) {
          if (!finished[j] && forks_available(i) && forks_available(j) && !overlap(i, j)) {
            eat(i);
            eat(j);
            printf("Philosophers %d and %d have finished eating\n", i + 1, j + 1);
            remaining -= 2;
            paired = 1;
            ate = 1;
            break;
          }
        }

        if (!paired && forks_available(i)) {
          eat(i);
          printf("Philosopher %d has finished eating\n", i + 1);
          remaining--;
          ate = 1;
        }

        if (ate) break;
      }
    }
  }
}

int main() {
  int hungry_count;
  printf("Enter number of hungry philosophers (0 to %d): ", N);
  scanf("%d", &hungry_count);

  if (hungry_count < 0 || hungry_count > N) {
    printf("Invalid number.\n");
    return 1;
  }

  int hungry[N] = {0};
  printf("Enter positions (1 to %d) of hungry philosophers:\n", N);

  for (int i = 0; i < hungry_count; i++) {
    int pos;
    scanf("%d", &pos);
    if (pos < 1 || pos > N) {
      printf("Invalid position.\n");
      return 1;
    }
    hungry[pos - 1] = 1;
  }

  for (int i = 0; i < N; i++)
    finished[i] = hungry[i] ? 0 : 1;

  simulate_one_eating();

  // Reset state
  for (int i = 0; i < N; i++) {
    forks[i] = 1;
    finished[i] = hungry[i] ? 0 : 1;
  }

  simulate_two_eating();

  return 0;
}


O/p:
Enter number of hungry philosophers (0 to 5): 3
Enter positions (1 to 5) of hungry philosophers:
1 2 5

Simulation: One philosopher eats at a time
Philosopher 1 is thinking
Philosopher 1 is eating
Philosopher 2 is thinking
Philosopher 2 is eating
Philosopher 5 is thinking
Philosopher 5 is eating

Simulation: Two philosophers eat at a time
Philosopher 1 is eating
Philosopher 1 has finished eating
Philosopher 2 is eating
Philosopher 5 is eating
Philosophers 2 and 5 have finished eating
