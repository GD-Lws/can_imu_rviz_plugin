/****************************************************************************
** Meta object code from reading C++ file 'imu_to_joint_panel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../can_imu_rviz_plugin/src/imu_to_joint_panel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imu_to_joint_panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel_t {
    QByteArrayData data[10];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel_t qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel = {
    {
QT_MOC_LITERAL(0, 0, 41), // "imu_to_joint_rviz_plugin::Imu..."
QT_MOC_LITERAL(1, 42, 14), // "euler_callback"
QT_MOC_LITERAL(2, 57, 0), // ""
QT_MOC_LITERAL(3, 58, 36), // "can_imu_lws::IMU_Euler_msg::C..."
QT_MOC_LITERAL(4, 95, 9), // "euler_msg"
QT_MOC_LITERAL(5, 105, 10), // "imu_id_set"
QT_MOC_LITERAL(6, 116, 9), // "startSpin"
QT_MOC_LITERAL(7, 126, 16), // "set_joint_offset"
QT_MOC_LITERAL(8, 143, 15), // "euler_to_radian"
QT_MOC_LITERAL(9, 159, 5) // "euler"

    },
    "imu_to_joint_rviz_plugin::ImuToJointPanel\0"
    "euler_callback\0\0can_imu_lws::IMU_Euler_msg::ConstPtr\0"
    "euler_msg\0imu_id_set\0startSpin\0"
    "set_joint_offset\0euler_to_radian\0euler"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_imu_to_joint_rviz_plugin__ImuToJointPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x09 /* Protected */,
       5,    0,   42,    2, 0x09 /* Protected */,
       6,    0,   43,    2, 0x09 /* Protected */,
       7,    0,   44,    2, 0x09 /* Protected */,
       8,    1,   45,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Float, QMetaType::Float,    9,

       0        // eod
};

void imu_to_joint_rviz_plugin::ImuToJointPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImuToJointPanel *_t = static_cast<ImuToJointPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->euler_callback((*reinterpret_cast< const can_imu_lws::IMU_Euler_msg::ConstPtr(*)>(_a[1]))); break;
        case 1: _t->imu_id_set(); break;
        case 2: _t->startSpin(); break;
        case 3: _t->set_joint_offset(); break;
        case 4: { float _r = _t->euler_to_radian((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject imu_to_joint_rviz_plugin::ImuToJointPanel::staticMetaObject = {
    { &rviz::Panel::staticMetaObject, qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel.data,
      qt_meta_data_imu_to_joint_rviz_plugin__ImuToJointPanel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *imu_to_joint_rviz_plugin::ImuToJointPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *imu_to_joint_rviz_plugin::ImuToJointPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_imu_to_joint_rviz_plugin__ImuToJointPanel.stringdata0))
        return static_cast<void*>(this);
    return rviz::Panel::qt_metacast(_clname);
}

int imu_to_joint_rviz_plugin::ImuToJointPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rviz::Panel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
