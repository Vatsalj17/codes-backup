<?php
/**
 * Registration Form Handler
 * Handles form submission from registration.html
 * 
 * Features:
 * - Input validation and sanitization
 * - Error handling
 * - Data processing
 * - Database storage (MySQL example)
 * - Email notification
 * - Success/Error responses
 */

// Start session for storing messages
session_start();

// Enable error reporting for development (disable in production)
error_reporting(E_ALL);
ini_set('display_errors', 1);

// Database configuration
define('DB_HOST', 'localhost');
define('DB_NAME', 'registration_db');
define('DB_USER', 'your_username');
define('DB_PASS', 'your_password');

/**
 * Database connection function
 */
function getDatabaseConnection() {
    try {
        $pdo = new PDO(
            "mysql:host=" . DB_HOST . ";dbname=" . DB_NAME . ";charset=utf8mb4",
            DB_USER,
            DB_PASS,
            [
                PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
                PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
                PDO::ATTR_EMULATE_PREPARES => false
            ]
        );
        return $pdo;
    } catch (PDOException $e) {
        error_log("Database connection failed: " . $e->getMessage());
        die("Database connection failed. Please try again later.");
    }
}

/**
 * Sanitize input data
 */
function sanitizeInput($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data, ENT_QUOTES, 'UTF-8');
    return $data;
}

/**
 * Validate email format
 */
function validateEmail($email) {
    return filter_var($email, FILTER_VALIDATE_EMAIL);
}

/**
 * Validate password strength
 */
function validatePassword($password) {
    // At least 8 characters, one uppercase, one lowercase, one number
    return preg_match('/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d@$!%*?&]{8,}$/', $password);
}

/**
 * Send email notification
 */
function sendEmailNotification($email, $username, $data) {
    $to = $email;
    $subject = "Registration Confirmation";
    $message = "
    <html>
    <head>
        <title>Registration Confirmation</title>
    </head>
    <body>
        <h2>Welcome to our platform, " . htmlspecialchars($username) . "!</h2>
        <p>Your registration has been successful.</p>
        <p><strong>Registration Details:</strong></p>
        <ul>
            <li>Username: " . htmlspecialchars($data['username']) . "</li>
            <li>Class: " . htmlspecialchars($data['class']) . "</li>
            <li>Subjects: " . htmlspecialchars(implode(', ', $data['subjects'])) . "</li>
            <li>City: " . htmlspecialchars($data['city']) . "</li>
        </ul>
        <p>Thank you for joining us!</p>
    </body>
    </html>
    ";
    
    $headers = "MIME-Version: 1.0" . "\r\n";
    $headers .= "Content-type:text/html;charset=UTF-8" . "\r\n";
    $headers .= 'From: noreply@yourwebsite.com' . "\r\n";
    
    return mail($to, $subject, $message, $headers);
}

/**
 * Process form data
 */
function processRegistration() {
    $errors = [];
    $data = [];
    
    // Check if form was submitted via POST (you should change form method to POST)
    if ($_SERVER['REQUEST_METHOD'] !== 'POST' && $_SERVER['REQUEST_METHOD'] !== 'GET') {
        $errors[] = "Invalid request method.";
        return ['success' => false, 'errors' => $errors];
    }
    
    // Use $_POST or $_GET based on form method (currently GET in your HTML)
    $input = $_SERVER['REQUEST_METHOD'] === 'POST' ? $_POST : $_GET;
    
    // Process first field (assuming it's email or name)
    $firstField = isset($input['first_field']) ? sanitizeInput($input['first_field']) : '';
    if (empty($firstField)) {
        // Check if it's in the first unnamed input (for your current HTML)
        $firstField = isset($input[array_keys($input)[0]]) && !in_array(array_keys($input)[0], ['username', 'password', 'class', 'subject', 'feedback']) 
                     ? sanitizeInput($input[array_keys($input)[0]]) 
                     : '';
    }
    
    if (empty($firstField)) {
        $errors[] = "First field is required.";
    } else {
        $data['first_field'] = $firstField;
    }
    
    // Process username
    $username = isset($input['username']) ? sanitizeInput($input['username']) : '';
    if (empty($username)) {
        $errors[] = "Username is required.";
    } elseif (strlen($username) < 3) {
        $errors[] = "Username must be at least 3 characters long.";
    } elseif (strlen($username) > 50) {
        $errors[] = "Username must not exceed 50 characters.";
    } elseif (!preg_match('/^[a-zA-Z0-9_]+$/', $username)) {
        $errors[] = "Username can only contain letters, numbers, and underscores.";
    } else {
        $data['username'] = $username;
    }
    
    // Process password
    $password = isset($input['password']) ? $input['password'] : '';
    if (empty($password)) {
        $errors[] = "Password is required.";
    } elseif (strlen($password) < 6) {
        $errors[] = "Password must be at least 6 characters long.";
    } else {
        // Hash the password for security
        $data['password'] = password_hash($password, PASSWORD_DEFAULT);
        $data['password_plain'] = $password; // For validation, remove in production
    }
    
    // Process class selection
    $class = isset($input['class']) ? sanitizeInput($input['class']) : '';
    if (empty($class)) {
        $errors[] = "Please select a class.";
    } elseif (!in_array($class, ['class XI', 'class XII'])) {
        $errors[] = "Invalid class selection.";
    } else {
        $data['class'] = $class;
    }
    
    // Process subject selection (checkboxes)
    $subjects = [];
    if (isset($input['subject'])) {
        if (is_array($input['subject'])) {
            foreach ($input['subject'] as $subject) {
                $subject = sanitizeInput($subject);
                if (in_array($subject, ['math', 'chem', 'phy', 'CS'])) {
                    $subjects[] = $subject;
                }
            }
        } else {
            $subject = sanitizeInput($input['subject']);
            if (in_array($subject, ['math', 'chem', 'phy', 'CS'])) {
                $subjects[] = $subject;
            }
        }
    }
    
    if (empty($subjects)) {
        $errors[] = "Please select at least one subject.";
    } else {
        $data['subjects'] = $subjects;
    }
    
    // Process city selection (note: your HTML select doesn't have a name attribute)
    $city = isset($input['city']) ? sanitizeInput($input['city']) : '';
    if (empty($city)) {
        // Try to get from select without name (this won't work with current HTML)
        $errors[] = "Please select a city. (Note: Add name='city' to select element in HTML)";
    } elseif (!in_array($city, ['Delhi', 'Banglore', 'Pune', 'Chennai'])) {
        $errors[] = "Invalid city selection.";
    } else {
        $data['city'] = $city;
    }
    
    // Process feedback
    $feedback = isset($input['feedback']) ? sanitizeInput($input['feedback']) : '';
    if (strlen($feedback) > 1000) {
        $errors[] = "Feedback must not exceed 1000 characters.";
    } else {
        $data['feedback'] = $feedback;
    }
    
    return [
        'success' => empty($errors),
        'errors' => $errors,
        'data' => $data
    ];
}

/**
 * Save data to database
 */
function saveToDatabase($data) {
    try {
        $pdo = getDatabaseConnection();
        
        // Prepare SQL statement
        $sql = "INSERT INTO registrations (first_field, username, password, class, subjects, city, feedback, created_at) 
                VALUES (:first_field, :username, :password, :class, :subjects, :city, :feedback, NOW())";
        
        $stmt = $pdo->prepare($sql);
        
        // Execute with data
        $result = $stmt->execute([
            ':first_field' => $data['first_field'],
            ':username' => $data['username'],
            ':password' => $data['password'],
            ':class' => $data['class'],
            ':subjects' => implode(',', $data['subjects']),
            ':city' => $data['city'] ?? '',
            ':feedback' => $data['feedback']
        ]);
        
        return $result;
    } catch (PDOException $e) {
        error_log("Database error: " . $e->getMessage());
        return false;
    }
}

/**
 * Main processing logic
 */
function main() {
    // Process the form
    $result = processRegistration();
    
    if (!$result['success']) {
        // Handle errors
        $_SESSION['errors'] = $result['errors'];
        header('Location: registration.html?error=1');
        exit;
    }
    
    $data = $result['data'];
    
    // Save to database
    if (!saveToDatabase($data)) {
        $_SESSION['errors'] = ['Failed to save registration. Please try again.'];
        header('Location: registration.html?error=1');
        exit;
    }
    
    // Send email notification (if first field is email)
    if (validateEmail($data['first_field'])) {
        sendEmailNotification($data['first_field'], $data['username'], $data);
    }
    
    // Success response
    $_SESSION['success_message'] = 'Registration completed successfully!';
    $_SESSION['registration_data'] = $data;
    
    // Redirect to success page or show success message
    header('Location: success.php');
    exit;
}

// Execute main function
main();

?>

<?php
/**
 * SQL to create the database table:
 * 
 * CREATE DATABASE IF NOT EXISTS registration_db;
 * USE registration_db;
 * 
 * CREATE TABLE IF NOT EXISTS registrations (
 *     id INT AUTO_INCREMENT PRIMARY KEY,
 *     first_field VARCHAR(255) NOT NULL,
 *     username VARCHAR(50) NOT NULL UNIQUE,
 *     password VARCHAR(255) NOT NULL,
 *     class ENUM('class XI', 'class XII') NOT NULL,
 *     subjects VARCHAR(255) NOT NULL,
 *     city VARCHAR(100),
 *     feedback TEXT,
 *     created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
 *     updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
 * );
 */
?>

<?php
/**
 * Additional files you should create:
 * 
 * 1. success.php - Success page
 * 2. config.php - Database configuration
 * 3. functions.php - Common functions
 * 
 * Also, update your HTML form:
 * - Add name attributes to all inputs
 * - Change method to POST for security
 * - Add name="city" to select element
 * - Add proper field names
 */
?>

<?php
/**
 * Suggested HTML form improvements:
 * 
 * <form action="/action.php" method="POST">
 *   <input type="email" name="email" placeholder="Email Address..." required /><br />
 *   <input type="text" name="username" placeholder="Username" required /><br />
 *   <input type="password" name="password" placeholder="Password" required /><br /><br />
 *   
 *   <h5>Select Class</h5>
 *   <label for="101">
 *     <input type="radio" value="class XI" name="class" id="101" required />class XI
 *   </label><br />
 *   <label for="102">
 *     <input type="radio" value="class XII" name="class" id="102" required />class XII
 *   </label>
 *   
 *   <h5>Select Fav Subjects</h5>
 *   <label for="103">
 *     <input type="checkbox" value="math" name="subject[]" id="103" />Maths
 *   </label>
 *   <label for="104">
 *     <input type="checkbox" value="chem" name="subject[]" id="104" />Chemistry
 *   </label>
 *   <label for="105">
 *     <input type="checkbox" value="phy" name="subject[]" id="105" />Physics
 *   </label>
 *   <label for="106">
 *     <input type="checkbox" value="CS" name="subject[]" id="106" />Computer Science
 *   </label><br><br>
 *   
 *   <h5>Select City</h5>
 *   <select name="city" required>
 *     <option value="">Choose City</option>
 *     <option value="Delhi">Delhi</option>
 *     <option value="Banglore">Banglore</option>
 *     <option value="Pune">Pune</option>
 *     <option value="Chennai">Chennai</option>
 *   </select><br /><br /><br />
 *   
 *   <textarea name="feedback" id="107" placeholder="Write your valuable feedback" rows="4" cols="30"></textarea><br><br>
 *   
 *   <input type="submit" value="Submit">
 * </form>
 */
?>
