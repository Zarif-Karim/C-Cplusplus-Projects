class Property {
    
    constructor(_name, _price, _color, _rent, _house_price) {
        this.name = _name;
        this.price = _price;
        this.owned = false;
        this.group = _color

        this.rent = _rent;
        
        this.houses = 0;
        this.house_price = _house_price;
    }

    get_rent() {
        return this.rent;
    }
}