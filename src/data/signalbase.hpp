/*
 * This file is part of the SmuView project.
 *
 * Copyright (C) 2012 Joel Holdsworth <joel@airwebreathe.org.uk>
 * Copyright (C) 2016 Soeren Apel <soeren@apelpie.net>
 * Copyright (C) 2017 Frank Stettner <frank-stettner@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DATA_SIGNALBASE_HPP
#define DATA_SIGNALBASE_HPP

#include <atomic>
#include <condition_variable>
#include <thread>
#include <vector>

#include <QColor>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QTimer>
#include <QVariant>

#include <libsigrokcxx/libsigrokcxx.hpp>

using std::atomic;
using std::condition_variable;
using std::map;
using std::mutex;
using std::pair;
using std::shared_ptr;
using std::vector;

namespace sigrok {
class Channel;
}

namespace sv {
namespace data {

class Analog;
class SignalData;

class SignalBase : public QObject
{
	Q_OBJECT

public:
	enum ChannelType {
		AnalogChannel = 1, ///< Analog data
		MathChannel    ///< Virtual channel generated by math operations
	};

private:
	static const int ColourBGAlpha;

public:
	SignalBase(shared_ptr<sigrok::Channel> sr_channel, ChannelType channel_type);
	virtual ~SignalBase();

public:
	/**
	 * Returns the underlying SR channel.
	 */
	shared_ptr<sigrok::Channel> sr_channel() const;

	/**
	 * Returns enabled status of this channel.
	 */
	bool enabled() const;

	/**
	 * Sets the enabled status of this channel.
	 * @param value Boolean value to set.
	 */
	void set_enabled(bool value);

	/**
	 * Gets the type of this channel.
	 */
	ChannelType type() const;

	/**
	 * Gets the index number of this channel, i.e. a unique ID assigned by
	 * the device driver.
	 */
	unsigned int index() const;

	/**
	 * Gets the name of this signal.
	 */
	QString name() const;

	/**
	 * Gets the internal name of this signal, i.e. how the device calls it.
	 */
	QString internal_name() const;

	/**
	 * Sets the name of the signal.
	 */
	virtual void set_name(QString name);

	/**
	 * Get the colour of the signal.
	 */
	QColor colour() const;

	/**
	 * Set the colour of the signal.
	 */
	void set_colour(QColor colour);

	/**
	 * Get the background colour of the signal.
	 */
	QColor bgcolour() const;

	/**
	 * Sets the internal data object.
	 */
	void set_data(shared_ptr<sv::data::SignalData> data);

	/**
	 * Get the internal data as analog data object in case of analog type.
	 */
	shared_ptr<sv::data::Analog> analog_data() const;

	virtual void save_settings(QSettings &settings) const;

	virtual void restore_settings(QSettings &settings);

Q_SIGNALS:
	void enabled_changed(const bool &value);

	void name_changed(const QString &name);

	void colour_changed(const QColor &colour);

	void samples_cleared();

	void samples_added(QObject* segment, uint64_t start_sample,
		uint64_t end_sample);

	void min_max_changed(float min, float max);

private Q_SLOTS:
	void on_samples_cleared();

	void on_samples_added(QObject* segment, uint64_t start_sample,
		uint64_t end_sample);

	void on_min_max_changed(float min, float max);

	void on_capture_state_changed(int state);

protected:
	shared_ptr<sigrok::Channel> sr_channel_;
	ChannelType channel_type_;
	shared_ptr<sv::data::SignalData> data_;

	float min_value_, max_value_;

	QString internal_name_, name_;
	QColor colour_, bgcolour_;
};

} // namespace data
} // namespace sv

#endif // DATA_SEGMENT_HPP
