//
// Created by 13466 on 2020/7/26.
//

#ifndef JTAPP_JTPLAYSTATUS_H
#define JTAPP_JTPLAYSTATUS_H


class JtPlaystatus {

public:
    bool exit = false;
    bool load = true;
    bool seek = false;
    bool pause = false;

public:
    JtPlaystatus();
    ~JtPlaystatus();

};


#endif //JTAPP_JTPLAYSTATUS_H
