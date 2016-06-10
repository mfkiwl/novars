/*
 *
 * This file is a part of NovaRS.
 *     
 * NovaRS, the GNSS station controlling software.
 * Copyright (C) 2016  Mykhailo Lytvyn
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef DAEMONIZE_H
#define DAEMONIZE_H

#include <syslog.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define PID_FILE "/var/run/NovaRS.pid"


volatile sig_atomic_t coughtShutdownSignal = 0;
volatile sig_atomic_t coughtHupSignal = 0;


void BecomeDaemon();
void SetupSignals();
void SignalHandler(int sig);


void BecomeDaemon()
{
    /* Forking   */
    pid_t childpid = fork();
    usleep(20000);

    if (childpid < 0)
    {
        syslog(LOG_ERR, "Can not fork from parent process. Exiting...");
        exit(EXIT_FAILURE);
    }

    /*  Close parent process  */
    if (childpid > 0)
    {
        exit(EXIT_SUCCESS);
    }
    /*  Change file mask  */
    umask(0);
    /*   SID    */
    pid_t sid = setsid();
    if (sid < 0)
    {
        syslog(LOG_ERR, "Can not get Session ID. Exiting...");
        exit(EXIT_FAILURE);
    }

    /* Create pid file */
    FILE* pidfile = NULL;
    /* If pid file exists, may be NTRIPclientCLI already running, so exit */
    if (access(PID_FILE, F_OK) == 0)
    {
        if (access(PID_FILE, R_OK) == 0)
        {
            pidfile = fopen(PID_FILE, "r");
            int old_pid = -1;
            char line[20];
            fgets(line, 20, pidfile);
            sscanf(line, "%d", &old_pid);
            syslog(LOG_WARNING, "program already running at PID %d. Delete PID file (%s) and restart application", old_pid, PID_FILE);
            fclose(pidfile);
            exit(-1);
        }
        syslog(LOG_WARNING, "PID file %s exists. Exiting...", PID_FILE);
        fclose(pidfile);
        exit(-1);
    }

    pidfile = fopen(PID_FILE, "w");
    pid_t pid = getpid();
    fprintf(pidfile, "%d", pid);
    fclose(pidfile);


    /* Changing directory to /     */
    if ((chdir("/")) < 0)
    {
        syslog(LOG_ERR, "Can not change to the root directory. Exiting...");
        exit(EXIT_FAILURE);
    }


    syslog(LOG_INFO, "Switched to daemon mode!");

    /* Close standard output */
    //close(STDIN_FILENO); // +++
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

}

void SetupSignals()
{
    /* Make signal handling */
    struct sigaction new_action;
    /* Set up the structure to specify the new action. */
    new_action.sa_handler = SignalHandler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;
    /* Set up the signal actions */
    sigaction(SIGHUP,  &new_action, NULL);
    sigaction(SIGQUIT, &new_action, NULL);
    sigaction(SIGTERM, &new_action, NULL);
    sigaction(SIGINT,  &new_action, NULL);
    signal(SIGPIPE, SIG_IGN);

}

void SignalHandler(int sig)
{
    char logMsg[100];
    switch (sig)
    {
    case SIGQUIT:
        sprintf(logMsg, "Programm will be stopped on signal %d (quit)", sig);
        coughtShutdownSignal = 1;
        break;
    case SIGTERM:
        sprintf(logMsg, "Programm will be stopped on signal %d (terminate)", sig);
        coughtShutdownSignal = 1;
        break;
    case SIGHUP:
        sprintf(logMsg, "Programm will be stopped on signal %d (hungup)", sig);
        coughtHupSignal = 1;
        break;
    case SIGINT: // When we press Ctrl-C
        sprintf(logMsg, "Programm will be stopped user request (interrupt from keyboard)");
        coughtHupSignal = 1;
        break;
    default:
        sprintf(logMsg, "Got signal %d. Ignoring...", sig);
        break;
    }


    syslog(LOG_INFO, "%s", logMsg);

}

// Remove PID file
void CleanUp()
{
    syslog(LOG_NOTICE, "Unlinking PID file");
    unlink("/var/run/NovaRS.pid");
}

#endif // DAEMONIZE_H

