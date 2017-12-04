/*
 * This file is part of the SmuView project.
 *
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

#include "baseview.hpp"
#include "src/session.hpp"

namespace sv {
namespace views {

const int BaseView::MaxViewAutoUpdateRate = 25; // No more than 25 Hz

BaseView::BaseView(Session &session, QWidget *parent) :
		QWidget(parent),
	session_(session)
{
	(void)parent;
}

Session& BaseView::session()
{
	return session_;
}

const Session& BaseView::session() const
{
	return session_;
}

void BaseView::save_settings(QSettings &settings) const
{
	(void)settings;
}

void BaseView::restore_settings(QSettings &settings)
{
	(void)settings;
}

} // namespace views
} // namespace sv