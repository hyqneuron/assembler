#ifndef YAML_SETTING_H
#define YAML_SETTING_H

#include <memory>
#include <vector>

namespace YAML
{
	class SettingChangeBase;
	
	template <typename T>
	class Setting
	{
	public:
		Setting(): m_value() {}
		
		const T get() const { return m_value; }
		std::auto_ptr <SettingChangeBase> set(const T& value);
		void restore(const Setting<T>& oldSetting) {
			m_value = oldSetting.get();
		}
		
	private:
		T m_value;
	};

	class SettingChangeBase
	{
	public:
		virtual ~SettingChangeBase() {}
		virtual void pop() = 0;
	};
	
	template <typename T>
	class SettingChange: public SettingChangeBase
	{
	public:
		SettingChange(Setting<T> *pSetting): m_pCurSetting(pSetting) {
			// copy old setting to save its state
			m_oldSetting = *pSetting;
		}
		
		virtual void pop() {
			m_pCurSetting->restore(m_oldSetting);
		}

	private:
		Setting<T> *m_pCurSetting;
		Setting<T> m_oldSetting;
	};

	template <typename T>
	inline std::auto_ptr <SettingChangeBase> Setting<T>::set(const T& value) {
		std::auto_ptr <SettingChangeBase> pChange(new SettingChange<T> (this));
		m_value = value;
		return pChange;
	}
	
	class SettingChanges
	{
	private:
		SettingChanges(const SettingChanges&);
		const SettingChanges& operator = (const SettingChanges&);
	public:
		SettingChanges() {}
		~SettingChanges() { clear(); }
		
		void clear() {
			restore();
			
			for(setting_changes::const_iterator it=m_settingChanges.begin();it!=m_settingChanges.end();++it)
				delete *it;
			m_settingChanges.clear();
		}
		
		void restore() {
			for(setting_changes::const_iterator it=m_settingChanges.begin();it!=m_settingChanges.end();++it)
				(*it)->pop();
		}
		
		void push(std::auto_ptr <SettingChangeBase> pSettingChange) {
			m_settingChanges.push_back(pSettingChange.release());
		}
		
		// like std::auto_ptr - assignment is transfer of ownership
		SettingChanges& operator = (SettingChanges& rhs) {
			if(this == &rhs)
				return *this;
			
			clear();
			m_settingChanges = rhs.m_settingChanges;
			rhs.m_settingChanges.clear();
			return *this;
		}
		
	private:
		typedef std::vector <SettingChangeBase *> setting_changes;
		setting_changes m_settingChanges;
	};
}

#endif
