pipeline {
    agent { docker { image 'ubuntu:16.04' } }
    
    stages {
        stage('Build') {
            steps {
                sh '''
                apt-get update
                apt-get -y install ranger
                gcc --version
                '''
            }
            steps {
                sh 'echo "I am done building stuff"'
            }
        }
        stage('UnitTests') {
            steps {
                sh 'echo "I am now testing stuff"'
            }
        }
    }
    post {
        always {
            sh 'echo "do cleanup"'
        }
    }
}