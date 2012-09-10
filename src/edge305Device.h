/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * GarminPlugin
 * Copyright (C) Andreas Diesner 2011 <garminplugin [AT] andreas.diesner [DOT] de>
 *
 * GarminPlugin is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GarminPlugin is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef EDGE305DEVICE_H_INCLUDED
#define EDGE305DEVICE_H_INCLUDED

#include <string>
#include "messageBox.h"
#include "gpsDevice.h"
#include "garmin.h"
#include "gpsFunctions.h"
#include "TcxBuilder/TcxBase.h"

using namespace std;

class MessageBox;

class Edge305Device : public GpsDevice
{
public:
    Edge305Device();

    Edge305Device(string name);

    virtual ~Edge305Device();


  /**
   * Starts a thread that tries to read the fitness data from a garmin device
   * @param dataTypeName - which type of data should be read from the device
   * @return int returns 1 if successful otherwise 0
   */
    int startReadFitnessData(string dataTypeName);

  /**
   * Returns the status of reading fitness data from the device
   * @return int     0 = idle    1 = working    2 = waiting    3 = finished
   */
    int finishReadFitnessData();

  /**
   * Gets the fitness data xml
   * @return xml containing fitness data read from garmin device
   */
    string getFitnessData();

    /**
     * Checks if a device is attached and returns the device name.
     * If no device is present and empty string is returned
     * @return string with device name
     */
    static string getAttachedDeviceName();

    string getDeviceDescription() const;
    int startWriteToGps(string filename, string xml);
    int finishWriteToGps();
    void cancelWriteToGps();
    int getTransferSucceeded();
    void setStorageCommand(string cmd);
    MessageBox * getMessage();
    void userAnswered(const int answer);
    bool isDeviceAvailable();

  /**
   * Starts reading the FIT data directory
   * @return int returns 1 if successful otherwise 0
   */
    virtual int startReadFITDirectory();

  /**
   * Checks status reading FIT data directory
   * @return 0 = idle 1 = working 2 = waiting 3 = finished
   */
    virtual int finishReadFITDirectory();

  /**
   * Cancels reading the FIT data directory
   */
    virtual void cancelReadFITDirectory();

  /**
   * Starts reading the fitness data without points
   * @param dataTypeName - which type of data should be read from the device
   * @return int returns 1 if successful otherwise 0
   */
    virtual int startReadFitnessDirectory(string dataTypeName);

  /**
   * Checks if the read of the fitness directory finished
   * @return 0 = idle 1 = working 2 = waiting 3 = finished
   */
    virtual int finishReadFitnessDirectory();

    /**
     * Cancels the read of the fitness data
     */
    virtual void cancelReadFitnessData();

    virtual int startReadFitnessDetail(string id);

    virtual int finishReadFitnessDetail();

    virtual void cancelReadFitnessDetail();


    /**
     * Start the reading of a file in the GPX format (like current.gpx on Oregon)
     */
    virtual int startReadFromGps();
    /**
     * This is used to indicate the status of the read process.
     * @return 0 = idle 1 = working 2 = waiting 3 = finished
     */
    virtual int finishReadFromGps();
    /**
     * Cancels the current read from the device.
     */
    virtual void cancelReadFromGps();

    virtual string getGpxData();

    /**
     * Returns a file from the device
     */
    virtual string getBinaryFile(string relativeFilePath);

    /**
     * Starts a binary file write to the device
     * @return number of urls detected in gpsDataString
     */
    virtual int startDownloadData(string gpsDataString);

    /**
     * Retrieves the next download url
     * @return url to download
     */
    virtual string getNextDownloadDataUrl();

    /**
     * This is used to indicate the status of the write download data process.
     * @return 0 = idle 1 = working 2 = waiting 3 = finished
     */
    virtual int finishDownloadData();

    /**
     * Writes some bytes into the file opened by startDownloadData
     * @return Bytes written to file
     */
    virtual int writeDownloadData(char *, int length);

    /**
     * Saves/Closes the current file
     */
    virtual void saveDownloadData();

    /**
     * Cancels the current file download
     */
    virtual void cancelDownloadData();

  /**
   * Starts a thread that writes the passed xml string to the given filename
   * @param filename - filename on disk
   * @param data - the filename to write to on the device.
   * @param dataTypeName - a Fitness DataType from the GarminDevice.xml retrieved with DeviceDescription
   * @return int returns 1 if successful otherwise 0
   */
    virtual int startWriteFitnessData(string filename, string data, string dataTypeName);

    /**
     * This is used to indicate the status of the write fitness data process.
     * @return 0 = idle 1 = working 2 = waiting 3 = finished
     */
    virtual int finishWriteFitnessData();

    /**
     * Cancels the current write of fitness data
     */
    virtual void cancelWriteFitnessData();

    /**
     * Returns the bytes available in the given path on the device
     * @return bytes available (-1 for non-mass storage mode devices.)
     */
    virtual int bytesAvailable(string path);

protected:
    virtual void doWork();
    void readFitnessDataFromDevice(bool readTrackData, string fitnessDetailId);

  /**
   * Directory where this device stores its fitness data
   */
    string fitnessDirectory;

    string fitnessFileExtension;

    /**
     * Reads fitnessdata xml from a garmin device like Edge 305/Forerunner 305
     * @return xml containing fitness data read from garmin device
     */
    string readFitnessData(bool readTrackData, string fitnessDetailId);

    /**
     * Reads fitnessdata into fitnessData xml from a garmin device like Edge 305/Forerunner 305
     * @return xml containing fitness data read from garmin device
     */
    TcxBase * readFitnessDataFromGarmin();

    /**
     * Starts reading from garmin device and stores gpx data in gpxDataGpsXml;
     */
    void readGpxDataFromDevice();

    /**
     * Reads the gpx data from the device and returns a string in gpx format
     */
    string readGpxData();

private:

    /**
     * Prints an activity read from the garmin device
     * @param run Garmin list of points describing the runs
     * @param lap Garmin list of points describing the laps
     * @param track Garmin list of points describing the tracks
     * @param garmin device descriptor
     * @return xml string that describes all activities provided by the given lists
     */
    TcxActivities * printActivities(garmin_list * runList, garmin_list * lap, garmin_list * track, const garmin_unit garmin);

    /**
     * Prints the header of a lap
     * @param D1011 internal lap format of garmintools
     * @param firstLap if set to true an <ID>Time</ID> header is added
     * @param printTrackData if <Track> should be outputted
     * @return xml string
     */
    TcxLap * getLapHeader(D1011 * lapData);
    TcxLap * getLapHeader(D1001 * lapData);

    /**
     * Prints a track point
     * @param D304 internal track point format of garmintools
     * @return xml string
     */
    TcxTrackpoint * getTrackPoint ( D304 * p);
    TcxTrackpoint * getTrackPoint ( D303 * p);

    /**
     * Prints information about the device
     * @param garmin device descriptor
     * @return xml string
     */
    TcxCreator * getCreator(const garmin_unit garmin);

    /**
     * Returns the state of the thread idle/busy/waiting/finished
     */
    int getThreadState();

  /**
   * Stores the fitnessData which was read from the device
   */
    string fitnessDataTcdXml;

  /**
   * Stores the gpxData which was read from the device
   */
    string gpxDataGpsXml;

    bool transferSuccessful;

    static string filterDeviceName(string name);

    string readFitnessDetailId;

   /**
    * Stores type of current run (0=Biking, 1=Running, 2=Other)
    */
    int runType;

   /**
    * Stores the fitness data read from current.gpx
    */
   TcxBase *fitnessData;

   bool _get_run_track_lap_info ( garmin_data * run,uint32 * track_index,uint32 * first_lap_index,uint32 * last_lap_index, uint8  * sport_type );

   uint32 getNextLapStartTime(garmin_list_node * node);
};



#endif // EDGE305DEVICE_H_INCLUDED
