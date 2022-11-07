/**
 * @file Worker.hpp
 * @author clement garrigues and nathan garnier (clement.garrigues@polymtl.ca and nathan.garnier@polymtl.ca)
 * @brief Qobject with process function
 * @version 0.1
 * @date 2022-11-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "qt5/QtCore/QObject"
#include "qt5/QtWidgets/QWidget"
#include <functional>
#include <string>
#ifndef __WORKER_H__
#define __WORKER_H__

class Worker : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Construct a new Worker object
     *
     * @param runFunction std::function<void(std::string,std::string)>  lambda function to execute
     * @param arg1 std::string first argument of the lambda function
     * @param arg2 std::string second argument of the lambda function
     */
    Worker(std::function<void(std::string, std::string)> runFunction, std::string arg1, std::string arg2);
    /**
     * @brief Destroy the Worker object
     *
     */
    ~Worker();

public slots:
    /**
     * @brief Function calling runFunction and triggered from outside
     *
     */
    void process();

signals:
    /**
     * @brief Function called when process ending
     *
     */
    void finished();
    /**
     * @brief Function called in case of error
     *
     * @param err QString containing the error
     */
    void err(QString err);

private:
    /**
     * @brief First argument of the function
     *
     */
    std::string arg1_;
    /**
     * @brief Second argument of the function
     *
     */
    std::string arg2_;
    /**
     * @brief std::function<void(std::string,std::string)>  Lambda function to execute
     *
     */
    std::function<void(std::string, std::string)> runFunction_;
};

#endif // __WORKER_H__