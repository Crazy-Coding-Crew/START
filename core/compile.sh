clang++ -std=c++11 -fPIC -shared -I/usr/include/python2.7/ -Iinclude/ -I../DB/include/ -L../DB/lib/ -lDB -lboost_python -lboost_program_options -lodb-pgsql -lodb -o Start_core.so src/App.cxx
