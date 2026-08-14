# spec file for package 
# rules v.1.0
#
# Copyright (c) 2026 RED SOFT
# The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package
# itself (unless the license for the pristine package is not an
# Open Source License, in which case the license is the MIT License).
#
# Copyright (c) 2026 РЕД СОФТ
# Лицензия на этот файл, а также на изменения и дополнения к файлу,
# является той же, что и для самого пакета (за исключением случаев,
# когда лицензия на пакет не является лицензией с открытым исходным
# кодом, в этом случае лицензией является лицензия MIT).

%if 0%{redos_version} < 0800
%global _lto_cflags %{nil}
%endif

Name:           hwreader
Summary:        Hardware information utility
Summary(ru):    Получение информации об оборудовании
URL:            https://github.com/DrumoDeD
License:        MIT

Epoch:          0
Version:        0.1
Release:        1%{?dist}

Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
BuildRequires:  pciutils-devel

Requires:       polkit
Requires:       dmidecode

%description
HWReader is a simple utility 
for retrieving basic hardware information, 
including the mainboard, processor, and DRAM memory.

%description -l ru
HWReader - простая утилита 
для получения основной информации об оборудовании, 
включающем материнскую плату, процессор, оперативную память.


%prep
%autosetup -n %{name}-%{version}

%build
%make_build

%install
%make_install

%clean
%make_clean

%files
%license LICENSE
%{_bindir}/HWReader
%{_libexecdir}/hwreader
%dir %{_sysconfdir}/hwreader
%{_sysconfdir}/hwreader/path.conf
%{_datadir}/polkit-1/actions/org.freedesktop.policykit.hwreader.policy

%changelog
* Fri Aug 14 2026 DrumoDeD <kokurinwork@yandex.ru> - 0:0.1-1
- Initial build
