#include<string>
#include<iostream>
#ifndef ROLE_HPP
#define ROLE_HPP
namespace final{
    
    class Fighter;
    class Protector;
    class Caster;

    class Base{
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        std::string name;
        int health,attack;
        bool alive,defensive;
        static int aliveNumber;
    public:
        Base(const std::string& name, const int health, const int attack)
            : name(name), health(health), attack(attack), alive(true), defensive(false) {
            aliveNumber++;
        }
        virtual ~Base() {}

        static int getAliveNumber() {
            return aliveNumber;
        }

        bool isAlive(){
            return alive;
        }

        bool isDefensive(){
            return defensive;
        }

        virtual void launch_attack(Base* target) = 0;
        virtual void defend(bool flag) = 0;
    };

    int Base::aliveNumber = 0;

    class Fighter:public Base{
    public:
        Fighter (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 3;
                attack += 2;
            } else {
                defensive = 0;
            }
        }
    };

    class Protector:public Base{
    public:
        Protector (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 7;
                attack += 1;
            } else {
                defensive = 0;
            }
        }
    };

    class Caster:public Base{
    public:
        Caster (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 5;
            } else {
                defensive = 0;
            }
        }
    };

    void Fighter::launch_attack(Base *target) {
        int mult = 1;
        if (dynamic_cast<Caster*>(target)) mult = 2;
        
        if (!target->defensive) {
            target->health -= this->attack * mult;
        } else {
            int damage = this->attack * mult - target->attack;
            if (damage > 0) target->health -= damage;
            this->health -= target->attack;
        }
        
        bool target_died = (target->health <= 0 && target->alive);
        bool self_died = (this->health <= 0 && this->alive);

        if (target_died) {
            target->alive = false;
            Base::aliveNumber--;
        }
        if (self_died) {
            this->alive = false;
            Base::aliveNumber--;
        }

        if (target_died) {
            std::string target_role;
            if (dynamic_cast<Fighter*>(target)) target_role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) target_role = "Protector";
            else if (dynamic_cast<Caster*>(target)) target_role = "Caster";
            std::cout << target_role << " " << target->name << " is killed" << std::endl;
        }
        if (self_died) {
            std::cout << "Fighter " << this->name << " is killed" << std::endl;
        }
    }

    void Protector::launch_attack(Base *target) {
        int mult = 1;
        if (dynamic_cast<Fighter*>(target)) mult = 2;
        
        if (!target->defensive) {
            target->health -= this->attack * mult;
        } else {
            int damage = this->attack * mult - target->attack;
            if (damage > 0) target->health -= damage;
            this->health -= target->attack;
        }

        bool target_died = (target->health <= 0 && target->alive);
        bool self_died = (this->health <= 0 && this->alive);

        if (target_died) {
            target->alive = false;
            Base::aliveNumber--;
        }
        if (self_died) {
            this->alive = false;
            Base::aliveNumber--;
        }

        if (target_died) {
            std::string target_role;
            if (dynamic_cast<Fighter*>(target)) target_role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) target_role = "Protector";
            else if (dynamic_cast<Caster*>(target)) target_role = "Caster";
            std::cout << target_role << " " << target->name << " is killed" << std::endl;
        }
        if (self_died) {
            std::cout << "Protector " << this->name << " is killed" << std::endl;
        }
    }

    void Caster::launch_attack(Base *target) {
        int mult = 1;
        if (dynamic_cast<Protector*>(target)) mult = 2;
        
        if (!target->defensive) {
            target->health -= this->attack * mult;
        } else {
            int damage = this->attack * mult - target->attack;
            if (damage > 0) target->health -= damage;
        }

        bool target_died = (target->health <= 0 && target->alive);
        bool self_died = (this->health <= 0 && this->alive);

        if (target_died) {
            target->alive = false;
            Base::aliveNumber--;
        }
        if (self_died) {
            this->alive = false;
            Base::aliveNumber--;
        }

        if (target_died) {
            std::string target_role;
            if (dynamic_cast<Fighter*>(target)) target_role = "Fighter";
            else if (dynamic_cast<Protector*>(target)) target_role = "Protector";
            else if (dynamic_cast<Caster*>(target)) target_role = "Caster";
            std::cout << target_role << " " << target->name << " is killed" << std::endl;
        }
        if (self_died) {
            std::cout << "Caster " << this->name << " is killed" << std::endl;
        }
    }
}
#endif //ROLE_HPP
