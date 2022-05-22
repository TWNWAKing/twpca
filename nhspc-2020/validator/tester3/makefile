CC = g++
OPTIONS = -std=c++1z -O3 -Wall -Wpedantic -Wextra

village_1: village_main.cc village_1.cc
	$(CC) $(OPTIONS) $^ -o $@

village_2: village_main.cc village_2.cc
	$(CC) $(OPTIONS) $^ -o $@

sample_1: sample_main.cc sample_1.cc
	$(CC) $(OPTIONS) $^ -o $@

sample_2: sample_main.cc sample_2.cc
	$(CC) $(OPTIONS) $^ -o $@

sample_3: sample_main.cc sample_3.cc
	$(CC) $(OPTIONS) $^ -o $@

fruit_1: fruit_main.cc fruit_1.cc
	$(CC) $(OPTIONS) $^ -o $@

fruit_2: fruit_main.cc fruit_2.cc
	$(CC) $(OPTIONS) $^ -o $@

fruit_3: fruit_main.cc fruit_3.cc
	$(CC) $(OPTIONS) $^ -o $@

fruit_4: fruit_main.cc fruit_4.cc
	$(CC) $(OPTIONS) $^ -o $@

matrix_0: matrix_main.cc matrix_0.cc
	$(CC) $(OPTIONS) -fopenmp $^ -o $@

matrix_1: matrix_main.cc matrix_1.cc
	$(CC) $(OPTIONS) -fopenmp $^ -o $@

matrix_2: matrix_main.cc matrix_2.cc
	$(CC) $(OPTIONS) -fopenmp $^ -o $@

matrix_3: matrix_main.cc matrix_3.cc
	$(CC) $(OPTIONS) -fopenmp $^ -o $@

run_village_1: village_1
	./village_1

run_village_2: village_2
	./village_2

run_sample_1: sample_1
	./sample_1

run_sample_2: sample_2
	./sample_2

run_sample_3: sample_3
	./sample_3

run_fruit_1: fruit_1
	./fruit_1

run_fruit_2: fruit_2
	./fruit_2

run_fruit_3: fruit_3
	./fruit_3

run_fruit_4: fruit_4
	./fruit_4

run_matrix_0: matrix_0
	./matrix_0

run_matrix_1: matrix_1
	./matrix_1

run_matrix_2: matrix_2
	./matrix_2

run_matrix_3: matrix_3
	./matrix_3

clean:
	rm -f village_1 village_2 sample_1 sample_2 sample_3 fruit_1 fruit_2 fruit_3 fruit_4 matrix_0 matrix_1 matrix_2 matrix_3
