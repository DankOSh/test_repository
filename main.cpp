/*
 * File:   main.cpp
 * Author: danijel.slivka
 *
 * Created on January 30, 2016, 5:26 PM
 */

#include <QCoreApplication>
#include <QObject>
#include <QThread>

class WorkerThread : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE {
        QString result;
        /* ... here is the expensive or blocking operation ... */
        emit resultReady(result);
    }
signals:
    void resultReady(const QString &s);
};

class Controller : public QThread
{
    Q_OBJECT
public:
    Controller();
	
    ~Controller() {
    }
	
public slots:
    void handleResults(const QString &);
	void startWorkInAThread();
};

void Controller::startWorkInAThread()
{
    WorkerThread *workerThread = new WorkerThread(this);
    connect(workerThread, &WorkerThread::resultReady, this, &Controller::handleResults);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

int main(int argc, char *argv[]) {
	// initialize resources, if needed
	// Q_INIT_RESOURCE(resfile);

	QCoreApplication app(argc, argv);
	
	Controller kontroler;
	kontroler.startWorkInAThread();

	// create and show your widgets here
	//setting for remote repository

	return app.exec();
	//testing the repository
}
