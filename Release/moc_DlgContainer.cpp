/****************************************************************************
** Meta object code from reading C++ file 'DlgContainer.h'
**
** Created: Tue Apr 14 09:44:35 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DlgContainer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DlgContainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomLabel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      23,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CustomLabel[] = {
    "CustomLabel\0\0clicked()\0CloseLabel()\0"
};

void CustomLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CustomLabel *_t = static_cast<CustomLabel *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->CloseLabel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CustomLabel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CustomLabel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CustomLabel,
      qt_meta_data_CustomLabel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CustomLabel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CustomLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CustomLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomLabel))
        return static_cast<void*>(const_cast< CustomLabel*>(this));
    return QWidget::qt_metacast(_clname);
}

int CustomLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CustomLabel::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CustomLabel::CloseLabel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_DlgContainer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      25,   13,   13,   13, 0x0a,
      41,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DlgContainer[] = {
    "DlgContainer\0\0emitBack()\0LabelSelected()\0"
    "LabelClosed()\0"
};

void DlgContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DlgContainer *_t = static_cast<DlgContainer *>(_o);
        switch (_id) {
        case 0: _t->emitBack(); break;
        case 1: _t->LabelSelected(); break;
        case 2: _t->LabelClosed(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DlgContainer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DlgContainer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DlgContainer,
      qt_meta_data_DlgContainer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DlgContainer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DlgContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DlgContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DlgContainer))
        return static_cast<void*>(const_cast< DlgContainer*>(this));
    return QWidget::qt_metacast(_clname);
}

int DlgContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DlgContainer::emitBack()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
