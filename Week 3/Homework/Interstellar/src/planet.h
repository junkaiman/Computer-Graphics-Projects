class planet {
public:
    
    glm::vec2 location, velocity, acceleration;
    float mass, g;
	float radius;
    planet() {}

    planet(float m, float x, float y, float g_) {
        mass = m;
		radius = 12 * m;
		location.x = x;
		location.y = y;
		acceleration *= 0;
        g = g_;
    }
    
    void applyForce(glm::vec2 force) {
        force /= mass;
        acceleration += force;
    }
    
    void update() {
        velocity += acceleration;
        location += velocity;
		acceleration *= 0;
    }
    
    void display() {
        ofSetLineWidth(2);
        ofSetColor(ofMap(mass, 0, 15, 180, 0));
        ofDrawCircle(location.x, location.y, radius);
    }
    
    glm::vec2 attract(planet m) {
        glm::vec2 force;
		force = location - m.location;
        float distance = force.length();
        distance = ofClamp(distance, 5.0, 1000);
		force = glm::normalize(force);
        float strength = (g * mass * m.mass) / (distance * distance);
        force *= strength;
        return force;
    }
};