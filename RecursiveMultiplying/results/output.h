#pragma once

void writeMPICH(char* filename, int64_t *dataset_raw);

void writeHDF5(int64_t id, int64_t size, segment_t segment, char* filename, char* schedule_string, size_t schedule_length, Stage schedule[], int64_t msgcounts_count, int64_t* msgcounts, int64_t* dataset_raw);
