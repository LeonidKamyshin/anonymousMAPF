#ifndef ANONYMOUSMAPF_SEARCHREQUEST_H
#define ANONYMOUSMAPF_SEARCHREQUEST_H

struct SearchRequest{
    int start_x, start_y, finish_x, finish_y;

    SearchRequest(int _start_x, int _start_y, int _finish_x, int _finish_y);
};
#endif //ANONYMOUSMAPF_SEARCHREQUEST_H
