#include "appthread.h"
#include <pthread.h>
#include <QCoreApplication>

void *StartQAppThread(void *threadArg) {
  InputArgs *args = (struct InputArgs*) threadArg;
  QCoreApplication app(args->argc, args->argv);
  app.exec();
  pthread_exit(NULL);
}

void StartAppThread(InputArgs &args) {
  pthread_t thread1;  
  int rc = pthread_create(&thread1, NULL, StartQAppThread, (void*)&args);
}
