/*
Copyright (C) 2019-2020 Matthew Milton

This file is part of the DataLogger.

DataLogger is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

DataLogger is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with DataLogger.  If not, see <https://www.gnu.org/licenses/>.
*/


#ifndef DATALOGGER_HPP
#define DATALOGGER_HPP

#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <string>

#include <iostream>

/**
    \brief a general data logger class template that provides capabilities to log data into memory
    that can be dumped to file

    This data logger logs words of most data types, but the data type must support output streams
    (in other words, the stream << operator) to be dumped to file.  Possible data types include
    intrinsic types (int,float,long,double,bool,etc.), std::string, Xilinx ap_fixed<> and ap_int<>,
    and any other type that supports output streams. All data words in a log must be same type.

    All data words are logged into one large allocation of memory organized by row and column.
    Each row is considered a collection of data words treated as a single sample window,
    with each column being a sampled data word.  A common setup is each row represents a time step
    or sample period, and the columns are the data sampled in this step/period.

    The data logger allocates memory of the data words based on the byte-size of the data word type,
    reported by sizeof() operator.  Note that this memory size will not consider the true size of
    a data word if the data type of the words has dynamic memory allocation or references (pointers,
    references, etc.), or is of classes with inheritance.
    Consider this situation when attempting to manage memory usage of an overall program when also
    using the data logger.

    This data logger type template is supported by C++03 and up.

    \tparam T data type of the words that will be logged by the data logger

    \note This class template is NOT HDL synthesizable for FPGA/ASIC development

    \author Matthew Milton
    \date 2019
    \version 1.0 (July 6, 2019)
**/
template< typename T >
class DataLogger
{

private:

    std::vector<T> memory;	///< vector for storing logger's contents
    long max_num_bytes;     ///< maximum number of bytes to be stored
    long max_num_samples;   ///< maximum number of sample words to be stored
    long max_num_rows;      ///< maximum number of rows to be stored
    long max_num_columns;   ///< maximum number of columns to be stored per row

    long row_position;		///< current row position
    long column_position;   ///< current column position
    long sample_count;      ///< current count of samples stored


public:

    /**
		\brief default constructor
    **/
    DataLogger() :
        memory(),
        max_num_bytes(0), max_num_samples(0),
        max_num_rows(0), max_num_columns(0),
        row_position(0), column_position(0),
        sample_count(0)
    {}

    /**
        @brief (re-)initializes the data logger to allocate space by memory size in bytes
        @param max_num_columns maximum number of elements per column in logger
        @param max_num_bytes memory size in bytes to allocate for logger
        @return maximum number of samples that be logged by logger
    **/
    long initializeByMemory(long max_num_columns, long max_num_bytes)
    {
        if( max_num_bytes < long(sizeof(T)) )
            throw std::invalid_argument("DataLogger<T>::initializeByMemory(): DataLogger cannot allocate memory less than size of given Type (in bytes).");

        if( max_num_columns < 0 )
            throw std::invalid_argument("DataLogger<T>::initializeByMemory(): Number of columns for DataLogger cannot be negative.");\

        if( long( max_num_columns*sizeof(T) ) > max_num_bytes)
            throw std::invalid_argument("DataLogger<T>::initializeByMemory(): Amount of memory requested for DataLogger is not enough for requested number of columns.");\

        this->max_num_bytes = max_num_bytes;
        this->max_num_columns = max_num_columns;
        this->max_num_rows = max_num_bytes / long(max_num_columns*sizeof(T));
        this->max_num_samples = max_num_columns*max_num_rows;

        try
        {
        	memory.clear();
			memory.reserve(max_num_rows*max_num_columns);
        }
        catch(...)
        {
            throw std::runtime_error("DataLogger<T>::initializeByMemory(): failed to allocate memory.  Try initializing with smaller amount of memory or columns.");
        }

        row_position = 0;
        column_position = 0;

        return max_num_samples;
    }

    /**
        @brief (re-)initializes the data logger to allocate log space by given number of rows and columns
        @param max_num_rows the maximum number of rows in the log
        @param max_num_columns the maximum number of columns in the log
        @return the amount of memory in bytes allocated for the log based on this log size and data word size
    **/
    long initializeByRowColumn(long max_num_rows, long max_num_columns)
    {
        if(max_num_columns < 0)
            throw std::invalid_argument("DataLogger<T>::initializeByRowColumn(): Number of columns for DataLogger cannot be negative.");\

        if(max_num_rows < 0)
            throw std::invalid_argument("DataLogger<T>::initializeByRowColumn(): Number of rows for DataLogger cannot be negative.");\

        memory.clear();

        try
        {
            memory.reserve(max_num_rows*max_num_columns);
        }
        catch(...)
        {
            throw std::runtime_error("DataLogger<T>::initializeByRowColumn(): failed to allocate memory.  Try smaller amount of rows or columns.");
        }

        this->max_num_bytes = max_num_rows*max_num_columns*sizeof(T);
        this->max_num_columns = max_num_columns;
        this->max_num_rows = max_num_rows;
        this->max_num_samples = max_num_columns*max_num_rows;

        row_position = 0;
        column_position = 0;

        return max_num_bytes;

    }

    inline long getMaxNumBytes() const
    {
        return max_num_bytes;
    }

    inline long getMaxNumSamples() const
    {
        return max_num_samples;
    }

    inline long getMaxNumRows() const
    {
        return max_num_rows;
    }

    inline long getMaxNumColumns() const
    {
        return max_num_columns;
    }

    inline long getRowPosition() const
    {
        return row_position;
    }

    inline long getColumnPosition() const
    {
        return column_position;
    }

    inline long getNumberOfSamples() const
    {
    	return sample_count;
    }

    inline const std::vector<T>& getMemory() const
    {
        return memory;
    }

    /**
		\brief [] operator overload to allow logger memory samples to be accessed as in 1D array
		\param i the 0-th index in the logger memory on where to access sample
		\return constant reference to the logged sample
		\throw nothing as no bound checks are made
    **/
    inline const T& operator[](long i) const
    {
    	return memory[i];
    }

    /**
		\brief gets sample from data logger at given 1D index in logger memory
		\param i the 0-th index in the logger memory on where to access sample
		\return constant reference to the logged sample
		\throw std::out_of_range if given index is out of range of memory
    **/
    inline const T& get(long i) const
    {
    	try
    	{
    		return memory.at(i);
    	}
    	catch(...)
    	{
    		throw std::out_of_range("DataLogger::get(long) -- given index is out of range of log memory");
    	}
    }

    /**
		\brief gets sample from data logger at given row and column indices
		\param row the 0-th row index to find sample
		\param col the 0-th column index to find sample
		\return constant reference to the logged sample
		\throw std::out_of_range if given index is out of range of memory
		\see get_fast(long,long) for faster get method without bound checks
    **/
    inline const T& get(long row, long col)
    {
    	try
    	{
    		return memory.at(row*max_num_columns + col);
    	}
    	catch(...)
    	{
    		throw std::out_of_range("DataLogger::get(long,long) -- given index is out of range of log memory");
    	}
    }

    /**
		\brief gets sample from data logger at given row and column indices
		\param row the 0-th row index to find sample
		\param col the 0-th column index to find sample
		\return constant reference to the logged sample
		\throw nothing as no bound checks are made
		\see get(long,long) for slower get method with bound checks
    **/
    inline const T& get_fast(long row, long col)
    {
    	return memory[row*max_num_columns + col];
    }

    /**
		\brief () operator overload for getting sample from data logger at given row and column
		indices
		\param row the 0-th row index to find sample
		\param col the 0-th column index to find sample
		\return constant reference to the logged sample
		\throw nothing as no bound checks are made
    **/
    inline const T& operator()(long row, long col)
    {
    	return memory[row*max_num_columns + col];
    }

    /**
		\return true if at row end, which is position past last column in current row; false
		otherwise

		Call this method to check if current row is filled.
    **/
    inline bool atRowEnd() const
    {
        return (column_position >= max_num_columns);
    }

    /**
		\return true if at log end, which is position past last row in logger; false otherwise

		Call this method to check if log is filled

		Any Attempt at logging samples if this method returns true will cause logger to throw error.

		\see isFull()
    **/
    inline bool atLogEnd() const
    {
        return (row_position >= max_num_rows);
    }

    /**
		\return true if current row is full; false otherwise

		This method is equivalent to atRowEnd()

		\see atRowEnd()
    **/
    inline bool isCurrentRowFull() const
    {
    	return (column_position >= max_num_columns);
    }

    /**
		\return true if log is full; false otherwise

		This method is equivalent to atLogEnd()

		\see atLogEnd()
    **/
    inline bool isFull() const
    {
    	return (row_position >= max_num_rows);
    }

    /**
		\brief logs a sample into the logger

		This method does <b>not</b> notify the user when end of row is reached.  It is up to the
		user to track when end of row is reached to prevent logging data into wrong row
		accidentally.

		\throw std::runtime error if log() is called when logger memory is full

		\param sample the sample of type T to log in current row
		\return reference to called logger (*this)
		\see isCurrentRowFull() and isFull() for methods to check if current row or entire log is full
    **/
    inline DataLogger<T>& log(T sample)
    {
        if( atRowEnd() )
        {
            column_position = 0;
            row_position++;
        }

        if(atLogEnd())
            throw std::runtime_error("DataLogger<T>::log(T) -- Cannot log sample when DataLogger memory is full.");

        memory.push_back(sample);

        column_position++;
        sample_count++;

        return *this;
    }

    /**
		\brief logs a sample into the logger through streaming

		This method does <b>not</b> notify the user when end of row is reached.  It is up to the
		user to track when end of row is reached to prevent logging data into wrong row
		accidentally.

		\throw std::runtime error if called when logger memory is full

		\param sample the sample of type T to log in current row
		\return reference to called logger (*this)
		\see isCurrentRowFull() and isFull() for methods to check if current row or entire log is full
    **/
    inline
    DataLogger<T>& operator<<(T sample)
    {
    	if( atRowEnd() )
        {
            column_position = 0;
            row_position++;
        }

        if(atLogEnd())
            throw std::runtime_error("DataLogger<T>::operator<<(T) -- Cannot log sample when DataLogger memory is full.");

        memory.push_back(sample);

        column_position++;
        sample_count++;

        return *this;
    }

    /**
		\brief fills the current sample row in logger and moves row position to next one

		The method is used to guarantee that current row in the logger is completely filled with
		samples.
		By calling this method, any remaining empty columns in current row will be set to given
		value s, and a new empty row will be started.  If current row is already full, then this
		method does nothing but start new row.

		This method can be used to initialize any new row, including first one, to all
		zeros/defaults.

		\param s the default value which to initialize remaining empty sample columns in current row
		\return reference to called logger (*this)
		\throw std::runtime_error if logger is full (atLogEnd() is true)
    **/
    inline
    DataLogger<T>& fillCurrentRow(const T& s= T())
    {
    	if( atRowEnd() )
        {
            column_position = 0;
            row_position++;
            return *this;
        }

        if(atLogEnd())
            throw std::runtime_error("DataLogger<T>::fillCurrentRow() -- data logger memory is full");

        while(!atRowEnd())
		{
			log(s);
		}

		return *this;
    }

    /**
		\brief dumps log contents to file as plain-text such as CSV or the like

		\throw std::runtime_error if method fails to open/create the log file

		\param filename filename of the file that log will be dumped to, including file extension
		\param delimiter delimiter used to separate samples in each row in log file; defaults to ", "
    **/
    void dumpToTextFile(std::string filename, std::string delimiter = ", ")
    {
        if(max_num_rows == 0 || max_num_columns == 0)
			throw std::runtime_error("DataLogger<T>::dumpToTextFile() -- data logger is not initialized and therefore cannot dump anything");

        std::fstream file;

        try
        {
            file.open(filename.c_str(), std::fstream::out | std::fstream::trunc);
        }
        catch(...)
        {
            throw std::runtime_error("DataLogger<>::dumpToTextFile() -- failed to open a file to dump log.");
        }

        file << std::setprecision(15);

        for(long r = 0; r < row_position+1; r++)
        {

            file << memory[r*max_num_columns + 0];

            for(long c = 1; c < max_num_columns; c++)
            {
                file
                << delimiter
                << memory[r*max_num_columns + c];
            }

            file << "\n";
        }

        file.close();
    }

    /**
		\brief dumps log contents to file as plain-text such as CSV or the like

		This overload of the method also includes the column titles for the samples into the first
		line of the created text file.

		\throw std::runtime_error if method fails to open/create the log file

		\param filename filename of the file that log will be dumped to, including file extension
		\param column_titles vector of titles that label each column of samples in the log file
		\param delimiter delimiter used to separate samples in each row in log file; defaults to ", "
    **/
    void dumpToTextFile(std::string filename, const std::vector<std::string>& column_titles, std::string delimiter = ", ")
    {
        if(max_num_rows == 0 || max_num_columns == 0)
			throw std::runtime_error("DataLogger<T>::dumpToTextFile() -- data logger is not initialized and therefore cannot dump anything");

		if(column_titles.size() != max_num_columns)
			throw std::invalid_argument("DataLogger<T>::dumpToTextFile() -- column_titles argument must have same number of titles as there are columns");

        std::fstream file;

        try
        {
            file.open(filename.c_str(), std::fstream::out | std::fstream::trunc);
        }
        catch(...)
        {
            throw std::runtime_error("DataLogger<>::dumpToTextFile() -- failed to open a file to dump log.");
        }

        std::vector<std::string>::const_iterator i = column_titles.begin();

        file << *i;

            //print file header
        for(i = ++i; i != column_titles.end(); i++)
        {
            file
            << delimiter
            << *i;
        }
        file << "\n";

        file << std::setprecision(15);

        for(long r = 0; r < row_position+1; r++)
        {

            file << memory[r*max_num_columns + 0];

            for(long c = 1; c < max_num_columns; c++)
            {
                file
                << delimiter
                << memory[r*max_num_columns + c];
            }

            file << "\n";
        }

        file.close();
    }

    /**
		\brief dumps log contents to file as plain-text ASCII file readable by MATLAB/Octave

		Data files created by this method can be opened in MATLAB/Octave by using the following
		command

		load filename.dat -ascii

		The above command in MATLAB/Octave will load the file into a double typed matrix with same
		name as the file given, sans file extension.

		Make sure file name extension is not .mat as that is interpreted as a special
		binary format for MATLAB.  Use extensions such as .dat or .txt, etc. instead.

		\throw std::runtime_error if method fails to open/create the log file

		\param filename filename of the file that log will be dumped to, including file extension
    **/
    void dumpToASCIIMatlabFile(std::string filename)
    {
    	dumpToTextFile(filename," ");
    }

    /**
		\brief dumps log contents to file as binary format

		This method is used as an alternative to dumpToTextFile() as this method should be faster
		than dumping to text file and binary file size should be significantly smaller.

		The binary file format is custom to this data logger.  The first lines are plain-text strings
		describing contents of the binary file; these lines are the header of the file.  After the
		header, the binary contents of the logger are stored.  The format is laid out exactly as
		follows:

		DATATYPE=<C++ data type of samples>\\n \n
		WORDSIZE=<word size of each sample>\\n \n
		NROWS=<number of sample rows, R>\\n \n
		NCOLUMNS=<number of sample columns, C>\\n \n
		<column title 1>,<column title 2>,...,<column title C>\\n \n
		<binary sample word contents to end of file, with no characters between them>

		Currently, the sample words in the log must be convertible to type double for this method
		as the method will store them as such.  The double float type is assumed to be 8 bytes,
		following IEC-60559 standard, which is expected on x86 and x86_64 platforms.

		The file format assumes reader of the log file has same (little/big) endianness as the
		writer of the file.  This method doesn't currently force endianess yet.

		If double float is not 8 bytes on given platform or endianness can not be guaranteed,
		consider using the dumpToTextFile() method instead for data logging which does not care
		about word size or endianness as samples are saved as delimited plain text.

		\see dumpToTextFile() for dumping log samples to delimited plain text files
		\see loadFromBinFile() for loading the binary log files back into memory

		\throw std::runtime_error if method fails to open/create the log file

		\param filename filename of the file that log will be dumped to, including file extension
		\param column_titles vector of titles that label each column of samples in the log file
    **/
    void dumpToBinFile(std::string filename, const std::vector<std::string>& column_titles)
    {
    	if(max_num_rows == 0 || max_num_columns == 0)
			throw std::runtime_error("DataLogger<T>::dumpToBinFile() -- data logger is not initialized and therefore cannot dump anything");

		if(column_titles.size() != max_num_columns)
			throw std::invalid_argument("DataLogger<T>::dumpToBinFile() -- column_titles argument must have same number of titles as there are columns");

    	std::fstream file;

        try
        {
            file.open(filename.c_str(), std::fstream::out | std::fstream::trunc);
        }
        catch(...)
        {
            throw std::runtime_error("DataLogger<>::dumpToBinFile() -- failed to open a file to dump log.");
        }

        const static std::string DATATYPE  = "DATATYPE=";
        const static std::string WORDSIZE  = "WORDSIZE=";
        const static std::string NROWS     = "NROWS=";
        const static std::string NCOLUMNS  = "NCOLUMNS=";
        const static char        DELIMITER = ',';

			//print file header

        file <<
        DATATYPE << "double"        << "\n" << //currently default to double float type
        WORDSIZE << sizeof(double)  << "\n" <<
        NROWS    << max_num_rows    << "\n" <<
        NCOLUMNS << max_num_columns << "\n";

        std::vector<std::string>::const_iterator i = column_titles.begin();

        file << *i;

        for(i = ++i; i != column_titles.end(); i++)
        {
            file
            << DELIMITER
            << *i;
        }
        file << "\n";

			//write to file the log data as double

		typename std::vector<T>::const_iterator iter = memory.begin();
        while(iter != memory.end())
        {
			double word = double(*iter); //currently store data as double for now
			const char* word_bytes = (const char*) &word;

			file.write(word_bytes, sizeof(double));

			iter++;
        }

        file.close();
    }

    /**
		\brief reads binary log file back into the data logger memory

		This method is used to load log file data into memory, the file written by the
		dumpToBinFile() method.

		The binary file format is custom to this data logger.  The first lines are plain-text strings
		describing contents of the binary file; these lines are the header of the file.  After the
		header, the binary contents of the logger are stored.  The format is laid out exactly as
		follows:

		DATATYPE=<C++ data type of samples>\\n \n
		WORDSIZE=<word size of each sample>\\n \n
		NROWS=<number of sample rows, R>\\n \n
		NCOLUMNS=<number of sample columns, C>\\n \n
		<column title 1>,<column title 2>,...,<column title C>\\n \n
		<binary sample word contents to end of file, with no characters between them>

		Currently, the sample words in the log must be convertible to type double for this method
		as the method will store them as such.  The double float type is assumed to be 8 bytes,
		following IEC-60559 standard, which is expected on x86 and x86_64 platforms.

		The file format assumes reader of the log file has same (little/big) endianness as the
		writer of the file.  This method doesn't currently force endianess yet.

		\see dumpToBinFile() for creation of the binary log files this method can read

		\throw std::runtime_error if method fails to open the log file

		\param filename filename of the file that log will be dumped to, including file extension
		\return string vector of titles that label each column of samples in the log file
    **/
	std::vector<std::string> loadFromBinFile(std::string filename)
	{
		std::fstream file;

        try
        {
            file.open(filename.c_str(), std::fstream::in);
        }
        catch(...)
        {
            throw std::runtime_error("DataLogger<>::loadFromBinFile() -- failed to open the file to read log.");
        }

        const static std::string DATATYPE  = "DATATYPE=";
        const static std::string WORDSIZE  = "WORDSIZE=";
        const static std::string NROWS     = "NROWS=";
        const static std::string NCOLUMNS  = "NCOLUMNS=";
        const static char        DELIMITER = ',';
        const static char        NEWLINE   = '\n';

        long file_rows = 0;
        long file_columns = 0;
        std::vector<std::string> file_column_header;

		//read header//

		std::string read_buf;
		std::string value_str;
		std::stringstream strstrm;
		int pos;

		std::getline(file,read_buf, NEWLINE); //read and ignore data type line for now
		std::getline(file,read_buf, NEWLINE); //read and ignore word size line for now; assume 8

			//read in nrows line
		std::getline(file,read_buf, NEWLINE);
		pos = read_buf.find('=') + 1;
		value_str = read_buf.substr(pos);
		strstrm << value_str;
		strstrm >> file_rows;
		strstrm.str(""); strstrm.clear();

			//read in ncolumns line
		std::getline(file,read_buf, NEWLINE);
		pos = read_buf.find('=') + 1;
		value_str = read_buf.substr(pos);
		strstrm << value_str;
		strstrm >> file_columns;
		strstrm.str(""); strstrm.clear();

			//read in column title line
		std::getline(file,read_buf, NEWLINE);
		read_buf += DELIMITER;
		strstrm << read_buf;

		for(long i = 0; i < file_columns; i++)
		{
            std::getline(strstrm,value_str,DELIMITER);
            file_column_header.push_back(value_str);
		}

		//read in data from file into data logger//

		initializeByRowColumn(file_rows, file_columns);

        for(long i = 0; i < file_rows*file_columns; i++)
		{
			double sample = 0;
			char* sample_bytes = (char*) &sample;
			file.read(sample_bytes,sizeof(double));
			log( T(sample) );
		}

		return file_column_header;
	}

};

#endif // DATALOGGER_HPP

