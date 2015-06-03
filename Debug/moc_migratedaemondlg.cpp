/****************************************************************************
** Meta object code from reading C++ file 'migratedaemondlg.h'
**
** Created: Tue Mar 31 10:16:07 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../migratedaemondlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'migratedaemondlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MigrateDaemonDlg[] = {

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
      24,   18,   17,   17, 0x0a,
      49,   18,   17,   17, 0x0a,
      74,   17,   17,   17, 0x0a,
      82,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MigrateDaemonDlg[] = {
    "MigrateDaemonDlg\0\0index\0"
    "ServerTypeChanged_1(int)\0"
    "ServerTypeChanged_2(int)\0GetIP()\0"
    "StartMigration()\0"
};

void MigrateDaemonDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MigrateDaemonDlg *_t = static_cast<MigrateDaemonDlg *>(_o);
        switch (_id) {
        case 0: _t->ServerTypeChanged_1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ServerTypeChanged_2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->GetIP(); break;
        case 3: _t->StartMigration(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MigrateDaemonDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MigrateDaemonDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MigrateDaemonDlg,
      qt_meta_data_MigrateDaemonDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MigrateDaemonDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MigrateDaemonDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MigrateDaemonDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MigrateDaemonDlg))
        return static_cast<void*>(const_cast< MigrateDaemonDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int MigrateDaemonDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
