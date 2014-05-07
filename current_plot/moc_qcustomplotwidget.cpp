/****************************************************************************
** Meta object code from reading C++ file 'qcustomplotwidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "QCustomGraph/qcustomplotwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcustomplotwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCustomPlotWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   57,   61,   61, 0x0a,
      62,   57,   61,   61, 0x0a,
      90,  112,   61,   61, 0x0a,
     114,  129,   61,   61, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QCustomPlotWidget[] = {
    "QCustomPlotWidget\0"
    "updateGraphData(dataVector,dataVector)\0"
    "x,y\0\0addGraphData(double,double)\0"
    "addGraphDataY(double)\0y\0savePlot(bool)\0"
    "state\0"
};

void QCustomPlotWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCustomPlotWidget *_t = static_cast<QCustomPlotWidget *>(_o);
        switch (_id) {
        case 0: _t->updateGraphData((*reinterpret_cast< dataVector(*)>(_a[1])),(*reinterpret_cast< dataVector(*)>(_a[2]))); break;
        case 1: _t->addGraphData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->addGraphDataY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->savePlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QCustomPlotWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCustomPlotWidget::staticMetaObject = {
    { &QCustomPlot::staticMetaObject, qt_meta_stringdata_QCustomPlotWidget,
      qt_meta_data_QCustomPlotWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCustomPlotWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCustomPlotWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCustomPlotWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCustomPlotWidget))
        return static_cast<void*>(const_cast< QCustomPlotWidget*>(this));
    return QCustomPlot::qt_metacast(_clname);
}

int QCustomPlotWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCustomPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
