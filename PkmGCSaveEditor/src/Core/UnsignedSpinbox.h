/*
* Copyright (C) TuxSH 2015
* This file is part of PkmGCSaveEditor.
*
* PkmGCSaveEditor is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PkmGCSaveEditor is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PkmGCSaveEditor.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _PKMGCSAVEEDITOR_UNSIGNED_SPINBOX_H
#define _PKMGCSAVEEDITOR_UNSIGNED_SPINBOX_H

#include <algorithm>
#include <QSpinBox>
namespace{
	template<unsigned int nb_bits> struct BMask{
		static const unsigned int bitmask = (int)((1U << nb_bits) - 1);
	};

	template<> struct BMask<32>{
		static const unsigned int bitmask = 0xffffffff; // to avoid compiler warnings
	};
}

template<unsigned int nb_bits = 32> // nb_bits must be <= 32
class UnsignedSpinbox : public QSpinBox{
public:
	static const unsigned int nbBits = nb_bits;
	static const int bitmask = BMask<nb_bits>::bitmask;

	UnsignedSpinbox(QWidget* parent = 0) : QSpinBox(parent){
			setRange(0, bitmask);
	}
	
	QValidator::State validate(QString& input, int& pos) const {
		QString stripped = input.trimmed();
		if (stripped.isEmpty()) return QValidator::Intermediate;

		bool ok;
		uint num = input.toUInt(&ok);
		if (!ok) return QValidator::Invalid;
		else if (num < m) return QValidator::Intermediate;
		else if (num > M) return QValidator::Invalid;
		else return QValidator::Acceptable;
	}
	

	
	int minimum(void) const {
		return (int)m;
	}
	uint unsignedMinimum(void) const {
		return m;
	}
	int maximum(void) const {
		return (int)M;
	}
	uint unsignedMaximum(void) const {
		return M;
	}

	void setMinimum(int min) {
		setRange(min, (int)M);
	}
	void setMaximum(int max) {
		setRange((int)m, max);
	}

	void setUnsignedMinimum(uint min) {
		setUnsignedRange(min, M);
	}
	void setUnsignedMaximum(uint max) {
		setUnsignedRange(m, max);
	}
	
	void setRange(int min, int max) {
		m = (uint)min;
		M = (uint)max;
		if (M > bitmask) M = bitmask;
		QSpinBox::setRange(INT_MIN, INT_MAX);
		setUnsignedValue(unsignedValue());
	}
	
	void setUnsignedRange(uint min, uint max) {
		setRange((int)min, (int)max);
	}

	uint unsignedValue(void) const{
		return (uint)(value());
	}

	void setUnsignedValue(uint val){
		if (val < m) val = m;
		if (val > M) val = M;
		QSpinBox::setValue((int)val);
	}
	int value(void) const {
		return (uint)QSpinBox::value();
	}
	void setValue(int val) {
		setUnsignedValue((uint)val);
	}

	void stepBy(int step) {
		uint uval = unsignedValue();
		if ((step > 0) && ((uval + step) < uval)) return; // overflow
		if ((step < 0) && (uval + step) > uval) return; // underflow
		setUnsignedValue(uval + step);
	}
protected:
	QString textFromValue(int val) const{
		return QString::number((uint)val );
	}

	int valueFromText(const QString& txt) const {
		return ((int)txt.toUInt());
	}
private:
	uint m, M;
};

#endif