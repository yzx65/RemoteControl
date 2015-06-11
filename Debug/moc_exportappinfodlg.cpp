/****************************************************************************
** Meta object code from reading C++ file 'exportappinfodlg.h'
**
** Created: Sun Jun 7 18:52:39 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../exportappinfodlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'exportappinfodlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExportAppInfoDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      32,   18,   17,   17, 0x05,
      55,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      74,   68,   17,   17, 0x0a,
      94,   17,   17,   17, 0x0a,
     113,   17,   17,   17, 0x0a,
     130,   17,   17,   17, 0x0a,
     147,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ExportAppInfoDlg[] = {
    "ExportAppInfoDlg\0\0path,targetId\0"
    "emitStart(QString,int)\0emitCancel()\0"
    "count\0GetRecordCount(int)\0CurrentRecordAdd()\0"
    "ExportFinished()\0ExportCanceled()\0"
    "OnBtnCancelClicked()\0"
};

void ExportAppInfoDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ExportAppInfoDlg *_t = static_cast<ExportAppInfoDlg *>(_o);
        switch (_id) {
        case 0: _t->emitStart((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->emitCancel(); break;
        case 2: _t->GetRecordCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->CurrentRecordAdd(); break;
        case 4: _t->ExportFinished(); break;
        case 5: _t->ExportCanceled(); break;
        case 6: _t->OnBtnCancelClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ExportAppInfoDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ExportAppInfoDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ExportAppInfoDlg,
      qt_meta_data_ExportAppInfoDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExportAppInfoDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExportAppInfoDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExportAppInfoDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExportAppInfoDlg))
        return static_cast<void*>(const_cast< ExportAppInfoDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int ExportAppInfoDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ExportAppInfoDlg::emitStart(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExportAppInfoDlg::emitCancel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
