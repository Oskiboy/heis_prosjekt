pipeline {
    agent { dockerfile true }

    stages {
        stage('Build') {
            steps {
                sh '''
                echo "Starting build..."
                gcc --version
                
                sh build.sh
                '''
                sh 'echo "Build complete..."'
            }
        }
        stage('UnitTests') {
            steps {
                sh 'echo "I am now testing stuff"'
                sh './build/HeisLab.bin'
            }
        }
    }
    post {
        always {
            sh '''
            echo "Starting clean"
            rm -f build/
            '''
        }
    }
}